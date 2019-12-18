#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_11__ {scalar_t__ e_kind; int e_flags; } ;
struct TYPE_10__ {size_t d_size; scalar_t__ d_type; size_t d_off; size_t d_align; int /*<<< orphan*/ * d_buf; } ;
struct TYPE_9__ {scalar_t__ sh_type; size_t sh_size; } ;
typedef  TYPE_1__ GElf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_2__ Elf_Data ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  DATA ; 
 int ELF_F_LAYOUT ; 
 scalar_t__ ELF_K_ELF ; 
 scalar_t__ ELF_T_BYTE ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SHT_STRTAB ; 
 TYPE_2__* elf_getdata (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * elf_getscn (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t roundup2 (size_t,size_t) ; 

char *
elf_strptr(Elf *e, size_t scndx, size_t offset)
{
	Elf_Scn *s;
	Elf_Data *d;
	GElf_Shdr shdr;
	uint64_t alignment, count;

	if (e == NULL || e->e_kind != ELF_K_ELF) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if ((s = elf_getscn(e, scndx)) == NULL ||
	    gelf_getshdr(s, &shdr) == NULL)
		return (NULL);

	if (shdr.sh_type != SHT_STRTAB ||
	    offset >= shdr.sh_size) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	d = NULL;
	if (e->e_flags & ELF_F_LAYOUT) {

		/*
		 * The application is taking responsibility for the
		 * ELF object's layout, so we can directly translate
		 * an offset to a `char *' address using the `d_off'
		 * members of Elf_Data descriptors.
		 */
		while ((d = elf_getdata(s, d)) != NULL) {

			if (d->d_buf == 0 || d->d_size == 0)
				continue;

			if (d->d_type != ELF_T_BYTE) {
				LIBELF_SET_ERROR(DATA, 0);
				return (NULL);
			}

			if (offset >= d->d_off &&
			    offset < d->d_off + d->d_size)
				return ((char *) d->d_buf + offset - d->d_off);
		}
	} else {
		/*
		 * Otherwise, the `d_off' members are not useable and
		 * we need to compute offsets ourselves, taking into
		 * account 'holes' in coverage of the section introduced
		 * by alignment requirements.
		 */
		count = (uint64_t) 0;	/* cumulative count of bytes seen */
		while ((d = elf_getdata(s, d)) != NULL && count <= offset) {

			if (d->d_buf == NULL || d->d_size == 0)
				continue;

			if (d->d_type != ELF_T_BYTE) {
				LIBELF_SET_ERROR(DATA, 0);
				return (NULL);
			}

			if ((alignment = d->d_align) > 1) {
				if ((alignment & (alignment - 1)) != 0) {
					LIBELF_SET_ERROR(DATA, 0);
					return (NULL);
				}
				count = roundup2(count, alignment);
			}

			if (offset < count) {
				/* offset starts in the 'hole' */
				LIBELF_SET_ERROR(ARGUMENT, 0);
				return (NULL);
			}

			if (offset < count + d->d_size) {
				if (d->d_buf != NULL)
					return ((char *) d->d_buf +
					    offset - count);
				LIBELF_SET_ERROR(DATA, 0);
				return (NULL);
			}

			count += d->d_size;
		}
	}

	LIBELF_SET_ERROR(ARGUMENT, 0);
	return (NULL);
}