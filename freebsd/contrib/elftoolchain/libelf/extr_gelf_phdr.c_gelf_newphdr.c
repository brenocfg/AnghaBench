#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  e_class; } ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _libelf_newphdr (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 

void *
gelf_newphdr(Elf *e, size_t count)
{
	if (e == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}
	return (_libelf_newphdr(e, e->e_class, count));
}