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
struct vm_area_struct {scalar_t__ vm_private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * map_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__ dispc ; 

__attribute__((used)) static void mmap_user_open(struct vm_area_struct *vma)
{
	int plane = (int)vma->vm_private_data;

	atomic_inc(&dispc.map_count[plane]);
}