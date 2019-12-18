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
typedef  void* u32 ;
struct __gxfifo {void* lo_mark; void* hi_mark; } ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */

void GX_InitFifoLimits(GXFifoObj *fifo,u32 hiwatermark,u32 lowatermark)
{
	struct __gxfifo *ptr = (struct __gxfifo*)fifo;

	ptr->hi_mark = hiwatermark;
	ptr->lo_mark = lowatermark;
}