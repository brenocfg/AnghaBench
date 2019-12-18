#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* ale_name; void* ale_value; } ;
typedef  TYPE_1__ alist_el_t ;

/* Variables and functions */

__attribute__((used)) static int
alist_dump_cb(void *node, void *private)
{
	int (*printer)(void *, void *) = private;
	alist_el_t *el = node;

	printer(el->ale_name, el->ale_value);

	return (1);
}