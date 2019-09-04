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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */

__attribute__((used)) static inline vm_offset_t *
get_backup_ptr(vm_size_t  elem_size,
               vm_offset_t *element)
{
	return (vm_offset_t *) ((vm_offset_t)element + elem_size - sizeof(vm_offset_t));
}