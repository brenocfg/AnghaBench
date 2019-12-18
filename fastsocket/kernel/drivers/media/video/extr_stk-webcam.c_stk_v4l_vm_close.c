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
struct vm_area_struct {struct stk_sio_buffer* vm_private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct stk_sio_buffer {scalar_t__ mapcount; TYPE_1__ v4lbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_FLAG_MAPPED ; 

__attribute__((used)) static void stk_v4l_vm_close(struct vm_area_struct *vma)
{
	struct stk_sio_buffer *sbuf = vma->vm_private_data;
	sbuf->mapcount--;
	if (sbuf->mapcount == 0)
		sbuf->v4lbuf.flags &= ~V4L2_BUF_FLAG_MAPPED;
}