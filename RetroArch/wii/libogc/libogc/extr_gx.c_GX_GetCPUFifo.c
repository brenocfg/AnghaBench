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
struct __gxfifo {int /*<<< orphan*/  gpfifo_ready; int /*<<< orphan*/  cpufifo_ready; int /*<<< orphan*/  fifo_wrap; int /*<<< orphan*/  lo_mark; int /*<<< orphan*/  hi_mark; int /*<<< orphan*/  rdwt_dst; int /*<<< orphan*/  wt_ptr; int /*<<< orphan*/  rd_ptr; int /*<<< orphan*/  size; int /*<<< orphan*/  buf_end; int /*<<< orphan*/  buf_start; } ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */
 int /*<<< orphan*/  GX_Flush () ; 
 int /*<<< orphan*/  __GX_SaveFifo () ; 
 int /*<<< orphan*/  _cpufifo ; 
 int /*<<< orphan*/  _gxcpufifoready ; 

void GX_GetCPUFifo(GXFifoObj *fifo)
{
	struct __gxfifo* ptr = (struct __gxfifo*)fifo;
	struct __gxfifo* cpufifo = (struct __gxfifo*)&_cpufifo;

	if(!_gxcpufifoready) return;

	GX_Flush();
	__GX_SaveFifo();

	ptr->buf_start = cpufifo->buf_start;
	ptr->buf_end = cpufifo->buf_end;
	ptr->size = cpufifo->size;
	ptr->rd_ptr = cpufifo->rd_ptr;
	ptr->wt_ptr = cpufifo->wt_ptr;
	ptr->rdwt_dst = cpufifo->rdwt_dst;
	ptr->hi_mark = cpufifo->hi_mark;
	ptr->lo_mark = cpufifo->lo_mark;
	ptr->fifo_wrap = cpufifo->fifo_wrap;
	ptr->cpufifo_ready = cpufifo->cpufifo_ready;
	ptr->gpfifo_ready = cpufifo->gpfifo_ready;
}