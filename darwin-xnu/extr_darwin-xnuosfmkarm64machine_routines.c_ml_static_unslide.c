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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 scalar_t__ gPhysBase ; 
 scalar_t__ gVirtBase ; 
 scalar_t__ ml_static_vtop (scalar_t__) ; 
 scalar_t__ vm_kernel_slide ; 

vm_offset_t
ml_static_unslide(
	vm_offset_t vaddr)
{
	return (ml_static_vtop(vaddr) - gPhysBase + gVirtBase - vm_kernel_slide) ;
}