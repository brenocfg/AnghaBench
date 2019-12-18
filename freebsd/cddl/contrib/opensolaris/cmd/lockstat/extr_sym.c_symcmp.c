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
struct TYPE_2__ {uintptr_t addr; } ;
typedef  TYPE_1__ syment_t ;

/* Variables and functions */

__attribute__((used)) static int
symcmp(const void *p1, const void *p2)
{
	uintptr_t a1 = ((syment_t *)p1)->addr;
	uintptr_t a2 = ((syment_t *)p2)->addr;

	if (a1 < a2)
		return (-1);
	if (a1 > a2)
		return (1);
	return (0);
}