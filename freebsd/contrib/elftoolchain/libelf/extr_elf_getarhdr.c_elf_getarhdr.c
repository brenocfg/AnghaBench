#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * e_arhdr; } ;
struct TYPE_6__ {int e_flags; TYPE_1__ e_hdr; } ;
typedef  int /*<<< orphan*/  Elf_Arhdr ;
typedef  TYPE_2__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int LIBELF_F_AR_HEADER ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _libelf_ar_gethdr (TYPE_2__*) ; 

Elf_Arhdr *
elf_getarhdr(Elf *e)
{
	if (e == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if (e->e_flags & LIBELF_F_AR_HEADER)
		return (e->e_hdr.e_arhdr);

	return (_libelf_ar_gethdr(e));
}