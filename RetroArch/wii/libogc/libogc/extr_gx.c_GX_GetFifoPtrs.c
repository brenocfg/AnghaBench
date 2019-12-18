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
struct __gxfifo {scalar_t__ wt_ptr; scalar_t__ rd_ptr; } ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */

void GX_GetFifoPtrs(GXFifoObj *fifo,void **rd_ptr,void **wt_ptr)
{
	struct __gxfifo *ptr = (struct __gxfifo*)fifo;
	*rd_ptr = (void*)ptr->rd_ptr;
	*wt_ptr = (void*)ptr->wt_ptr;
}