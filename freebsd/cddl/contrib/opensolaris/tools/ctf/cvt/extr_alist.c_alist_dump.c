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
struct TYPE_3__ {int /*<<< orphan*/  al_elements; } ;
typedef  TYPE_1__ alist_t ;

/* Variables and functions */
 int alist_def_print_cb (void*,void*) ; 
 int /*<<< orphan*/  alist_dump_cb ; 
 int hash_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
alist_dump(alist_t *alist, int (*printer)(void *, void *))
{
	if (!printer)
		printer = alist_def_print_cb;

	return (hash_iter(alist->al_elements, alist_dump_cb, (void *)printer));
}