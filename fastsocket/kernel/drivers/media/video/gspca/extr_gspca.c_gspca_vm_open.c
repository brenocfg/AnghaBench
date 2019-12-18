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
struct vm_area_struct {struct gspca_frame* vm_private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct gspca_frame {TYPE_1__ v4l2_buf; int /*<<< orphan*/  vma_use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 

__attribute__((used)) static void gspca_vm_open(struct vm_area_struct *vma)
{
	struct gspca_frame *frame = vma->vm_private_data;

	frame->vma_use_count++;
	frame->v4l2_buf.flags |= V4L2_BUF_FLAG_MAPPED;
}