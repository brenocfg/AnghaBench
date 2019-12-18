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
struct __gxfifo {void* rd_ptr; scalar_t__ size; void* rdwt_dst; void* wt_ptr; } ;
typedef  void* s32 ;
typedef  int /*<<< orphan*/  GXFifoObj ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (void*) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (void*) ; 

void GX_InitFifoPtrs(GXFifoObj *fifo,void *rd_ptr,void *wt_ptr)
{
	u32 level;
	s32 rdwt_dst;
	struct __gxfifo *ptr = (struct __gxfifo*)fifo;

	_CPU_ISR_Disable(level);
	rdwt_dst =  wt_ptr-rd_ptr;
	ptr->rd_ptr = (u32)rd_ptr;
	ptr->wt_ptr = (u32)wt_ptr;
	ptr->rdwt_dst = rdwt_dst;
	if(rdwt_dst<0) {
		rdwt_dst += ptr->size;
		ptr->rd_ptr = rdwt_dst;
	}
	_CPU_ISR_Restore(level);
}