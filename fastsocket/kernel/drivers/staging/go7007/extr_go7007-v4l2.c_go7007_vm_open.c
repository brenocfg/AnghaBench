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
struct vm_area_struct {struct go7007_buffer* vm_private_data; } ;
struct go7007_buffer {int /*<<< orphan*/  mapped; } ;

/* Variables and functions */

__attribute__((used)) static void go7007_vm_open(struct vm_area_struct *vma)
{
	struct go7007_buffer *gobuf = vma->vm_private_data;

	++gobuf->mapped;
}