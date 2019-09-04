#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint32_t ;
struct fat_header {int /*<<< orphan*/  nfat_arch; int /*<<< orphan*/  magic; } ;
struct fat_arch {int /*<<< orphan*/  cpusubtype; int /*<<< orphan*/  cputype; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  load_return_t ;

/* Variables and functions */
 scalar_t__ FAT_MAGIC ; 
 int /*<<< orphan*/  LOAD_BADMACHO ; 
 int /*<<< orphan*/  LOAD_FAILURE ; 
 int /*<<< orphan*/  LOAD_SUCCESS ; 
 scalar_t__ OSSwapBigToHostInt32 (int /*<<< orphan*/ ) ; 
 scalar_t__ UINT32_MAX ; 

load_return_t
fatfile_validate_fatarches(vm_offset_t data_ptr, vm_size_t data_size)
{
	uint32_t magic, nfat_arch;
	uint32_t max_nfat_arch, i, j;
	uint32_t fat_header_size;

	struct fat_arch		*arches;
	struct fat_header	*header;

	if (sizeof(struct fat_header) > data_size) {
		return (LOAD_FAILURE);
	}

	header = (struct fat_header *)data_ptr;
	magic = OSSwapBigToHostInt32(header->magic);
	nfat_arch = OSSwapBigToHostInt32(header->nfat_arch);

	if (magic != FAT_MAGIC) {
		/* must be FAT_MAGIC big endian */
		return (LOAD_FAILURE);
	}

	max_nfat_arch = (data_size - sizeof(struct fat_header)) / sizeof(struct fat_arch);
	if (nfat_arch > max_nfat_arch) {
		/* nfat_arch would cause us to read off end of buffer */
		return (LOAD_BADMACHO);
	}

	/* now that we know the fat_arch list fits in the buffer, how much does it use? */
	fat_header_size = sizeof(struct fat_header) + nfat_arch * sizeof(struct fat_arch);
	arches = (struct fat_arch *)(data_ptr + sizeof(struct fat_header));

	for (i=0; i < nfat_arch; i++) {
		uint32_t i_begin = OSSwapBigToHostInt32(arches[i].offset);
		uint32_t i_size = OSSwapBigToHostInt32(arches[i].size);
		uint32_t i_cputype = OSSwapBigToHostInt32(arches[i].cputype);
		uint32_t i_cpusubtype = OSSwapBigToHostInt32(arches[i].cpusubtype);

		if (i_begin < fat_header_size) {
			/* slice is trying to claim part of the file used by fat headers themselves */
			return (LOAD_BADMACHO);
		}

		if ((UINT32_MAX - i_size) < i_begin) {
			/* start + size would overflow */
			return (LOAD_BADMACHO);
		}
		uint32_t i_end = i_begin + i_size;

		for (j=i+1; j < nfat_arch; j++) {
			uint32_t j_begin = OSSwapBigToHostInt32(arches[j].offset);
			uint32_t j_size = OSSwapBigToHostInt32(arches[j].size);
			uint32_t j_cputype = OSSwapBigToHostInt32(arches[j].cputype);
			uint32_t j_cpusubtype = OSSwapBigToHostInt32(arches[j].cpusubtype);

			if ((i_cputype == j_cputype) && (i_cpusubtype == j_cpusubtype)) {
				/* duplicate cputype/cpusubtype, results in ambiguous references */
				return (LOAD_BADMACHO);
			}

			if ((UINT32_MAX - j_size) < j_begin) {
				/* start + size would overflow */
				return (LOAD_BADMACHO);
			}
			uint32_t j_end = j_begin + j_size;

			if (i_begin <= j_begin) {
				if (i_end <= j_begin) {
					/* I completely precedes J */
				} else {
					/* I started before J, but ends somewhere in or after J */
					return (LOAD_BADMACHO);
				}
			} else {
				if (i_begin >= j_end) {
					/* I started after J started but also after J ended */
				} else {
					/* I started after J started but before it ended, so there is overlap */
					return (LOAD_BADMACHO);
				}
			}
		}
	}

	return (LOAD_SUCCESS);
}