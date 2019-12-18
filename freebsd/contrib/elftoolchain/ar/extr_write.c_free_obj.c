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
struct ar_obj {struct ar_obj* name; scalar_t__ elf; } ;

/* Variables and functions */
 int /*<<< orphan*/  elf_end (scalar_t__) ; 
 int /*<<< orphan*/  free (struct ar_obj*) ; 

__attribute__((used)) static void
free_obj(struct ar_obj *obj)
{
	if (obj->elf)
		elf_end(obj->elf);

	free(obj->name);
	free(obj);
}