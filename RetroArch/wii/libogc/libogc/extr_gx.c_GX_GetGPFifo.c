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
struct __gxfifo {int /*<<< orphan*/  cpufifo_ready; int /*<<< orphan*/  gpfifo_ready; int /*<<< orphan*/  fifo_wrap; int /*<<< orphan*/  lo_mark; int /*<<< orphan*/  hi_mark; int /*<<< orphan*/  rdwt_dst; int /*<<< orphan*/  wt_ptr; int /*<<< orphan*/  rd_ptr; int /*<<< orphan*/  size; int /*<<< orphan*/  buf_end; int /*<<< orphan*/  buf_start; } ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */
 int /*<<< orphan*/  __GX_SaveFifo () ; 
 int /*<<< orphan*/  _gpfifo ; 
 int /*<<< orphan*/  _gxgpfifoready ; 

void GX_GetGPFifo(GXFifoObj *fifo)
{
	struct __gxfifo* ptr = (struct __gxfifo*)fifo;
	struct __gxfifo* gpfifo = (struct __gxfifo*)&_gpfifo;

	if(!_gxgpfifoready) return;

	__GX_SaveFifo();

	ptr->buf_start = gpfifo->buf_start;
	ptr->buf_end = gpfifo->buf_end;
	ptr->size = gpfifo->size;
	ptr->rd_ptr = gpfifo->rd_ptr;
	ptr->wt_ptr = gpfifo->wt_ptr;
	ptr->rdwt_dst = gpfifo->rdwt_dst;
	ptr->hi_mark = gpfifo->hi_mark;
	ptr->lo_mark = gpfifo->lo_mark;
	ptr->fifo_wrap = gpfifo->fifo_wrap;
	ptr->gpfifo_ready = gpfifo->gpfifo_ready;
	ptr->cpufifo_ready = gpfifo->cpufifo_ready;
}