#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t s_ndx; } ;
typedef  TYPE_1__ Elf_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SHN_UNDEF ; 

size_t
elf_ndxscn(Elf_Scn *s)
{
	if (s == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (SHN_UNDEF);
	}
	return (s->s_ndx);
}