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
typedef  int u32 ;
struct __gxfifo {int buf_start; int buf_end; int size; scalar_t__ rdwt_dst; } ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */
 scalar_t__ GX_FIFO_HIWATERMARK ; 
 int GX_FIFO_MINSIZE ; 
 int /*<<< orphan*/  GX_InitFifoLimits (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  GX_InitFifoPtrs (int /*<<< orphan*/ *,void*,void*) ; 

void GX_InitFifoBase(GXFifoObj *fifo,void *base,u32 size)
{
	struct __gxfifo *ptr = (struct __gxfifo*)fifo;

	if(!ptr || size<GX_FIFO_MINSIZE) return;

	ptr->buf_start = (u32)base;
	ptr->buf_end = (u32)base + size - 4;
	ptr->size = size;
	ptr->rdwt_dst = 0;

	GX_InitFifoLimits(fifo,(size-GX_FIFO_HIWATERMARK),((size>>1)&0x7fffffe0));
	GX_InitFifoPtrs(fifo,base,base);
}