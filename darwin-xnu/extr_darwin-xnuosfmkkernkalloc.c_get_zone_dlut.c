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
typedef  int /*<<< orphan*/  zone_t ;
typedef  int /*<<< orphan*/  vm_size_t ;

/* Variables and functions */
 long INDEX_ZDLUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * k_zone ; 
 scalar_t__* k_zone_dlut ; 

__attribute__((used)) static __inline zone_t
get_zone_dlut(vm_size_t size)
{
	long dindex = INDEX_ZDLUT(size);
	int zindex = (int)k_zone_dlut[dindex];
	return (k_zone[zindex]);
}