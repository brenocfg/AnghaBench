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
struct vm_area_struct {struct sn9c102_frame_t* vm_private_data; } ;
struct sn9c102_frame_t {int /*<<< orphan*/  vma_use_count; } ;

/* Variables and functions */

__attribute__((used)) static void sn9c102_vm_open(struct vm_area_struct* vma)
{
	struct sn9c102_frame_t* f = vma->vm_private_data;
	f->vma_use_count++;
}