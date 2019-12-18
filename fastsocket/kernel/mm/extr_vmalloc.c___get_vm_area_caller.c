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
struct vm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vm_struct* __get_vm_area_node (unsigned long,int,unsigned long,unsigned long,unsigned long,int,int /*<<< orphan*/ ,void*) ; 

struct vm_struct *__get_vm_area_caller(unsigned long size, unsigned long flags,
				       unsigned long start, unsigned long end,
				       void *caller)
{
	return __get_vm_area_node(size, 1, flags, start, end, -1, GFP_KERNEL,
				  caller);
}