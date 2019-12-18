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
struct TYPE_2__ {scalar_t__ ale_name; } ;
typedef  TYPE_1__ alist_el_t ;

/* Variables and functions */

__attribute__((used)) static int
alist_cmp(void *arg1, void *arg2)
{
	alist_el_t *el1 = arg1;
	alist_el_t *el2 = arg2;
	return ((uintptr_t)el1->ale_name != (uintptr_t)el2->ale_name);
}