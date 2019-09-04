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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_object_offset_t ;
struct TYPE_3__ {int /*<<< orphan*/  vmp_offset; } ;

/* Variables and functions */

vm_object_offset_t
vm_page_get_offset(vm_page_t page)
{
	return (page->vmp_offset);
}