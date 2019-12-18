#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t e_nscn; } ;
struct TYPE_13__ {TYPE_1__ e_elf; } ;
struct TYPE_16__ {int e_class; TYPE_2__ e_u; } ;
struct TYPE_15__ {scalar_t__ d_size; scalar_t__ d_buf; } ;
struct TYPE_14__ {int sh_flags; scalar_t__ sh_type; } ;
typedef  TYPE_3__ GElf_Shdr ;
typedef  int /*<<< orphan*/  GElf_Ehdr ;
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  TYPE_4__ Elf_Data ;
typedef  TYPE_5__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  CLASS ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SHF_ALLOC ; 
 scalar_t__ SHT_DYNAMIC ; 
 scalar_t__ SHT_DYNSYM ; 
 unsigned long _libelf_sum (unsigned long,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * elf_getscn (TYPE_5__*,size_t) ; 
 TYPE_4__* elf_rawdata (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * gelf_getehdr (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gelf_getshdr (int /*<<< orphan*/ *,TYPE_3__*) ; 

long
_libelf_checksum(Elf *e, int elfclass)
{
	size_t shn;
	Elf_Scn *scn;
	Elf_Data *d;
	unsigned long checksum;
	GElf_Ehdr eh;
	GElf_Shdr shdr;

	if (e == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0L);
	}

	if (e->e_class != elfclass) {
		LIBELF_SET_ERROR(CLASS, 0);
		return (0L);
	}

	if (gelf_getehdr(e, &eh) == NULL)
		return (0);

	/*
	 * Iterate over all sections in the ELF file, computing the
	 * checksum along the way.
	 *
	 * The first section is always SHN_UNDEF and can be skipped.
	 * Non-allocatable sections are skipped, as are sections that
	 * could be affected by utilities such as strip(1).
	 */

	checksum = 0;
	for (shn = 1; shn < e->e_u.e_elf.e_nscn; shn++) {
		if ((scn = elf_getscn(e, shn)) == NULL)
			return (0);
		if (gelf_getshdr(scn, &shdr) == NULL)
			return (0);
		if ((shdr.sh_flags & SHF_ALLOC) == 0 ||
		    shdr.sh_type == SHT_DYNAMIC ||
		    shdr.sh_type == SHT_DYNSYM)
			continue;

		d = NULL;
		while ((d = elf_rawdata(scn, d)) != NULL)
			checksum = _libelf_sum(checksum,
			    (unsigned char *) d->d_buf, (size_t) d->d_size);
	}

	/*
	 * Return a 16-bit checksum compatible with Solaris.
	 */
	return (long) (((checksum >> 16) & 0xFFFFUL) + (checksum & 0xFFFFUL));
}