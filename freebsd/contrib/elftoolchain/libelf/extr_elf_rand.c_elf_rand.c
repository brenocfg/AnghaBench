#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ar_hdr {char* ar_fmag; } ;
typedef  int off_t ;
struct TYPE_5__ {int e_next; } ;
struct TYPE_6__ {TYPE_1__ e_ar; } ;
struct TYPE_7__ {scalar_t__ e_kind; size_t e_rawsize; TYPE_2__ e_u; scalar_t__ e_rawfile; } ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF_K_AR ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SARMAG ; 

off_t
elf_rand(Elf *ar, off_t offset)
{
	struct ar_hdr *arh;

	if (ar == NULL || ar->e_kind != ELF_K_AR ||
	    (offset & 1) || offset < SARMAG ||
	    (size_t) offset + sizeof(struct ar_hdr) >= ar->e_rawsize) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return 0;
	}

	arh = (struct ar_hdr *) (ar->e_rawfile + offset);

	/* a too simple sanity check */
	if (arh->ar_fmag[0] != '`' || arh->ar_fmag[1] != '\n') {
		LIBELF_SET_ERROR(ARCHIVE, 0);
		return 0;
	}

	ar->e_u.e_ar.e_next = offset;

	return (offset);
}