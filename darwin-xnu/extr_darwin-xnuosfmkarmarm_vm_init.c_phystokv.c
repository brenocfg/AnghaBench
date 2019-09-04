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
typedef  scalar_t__ vm_map_address_t ;
typedef  scalar_t__ pmap_paddr_t ;

/* Variables and functions */
 scalar_t__ gPhysBase ; 
 scalar_t__ gVirtBase ; 

vm_map_address_t
phystokv(pmap_paddr_t pa)
{
	return (pa - gPhysBase + gVirtBase);
}