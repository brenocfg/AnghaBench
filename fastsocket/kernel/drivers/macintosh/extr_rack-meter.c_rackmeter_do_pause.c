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
typedef  int /*<<< orphan*/  u32 ;
struct rackmeter_dma {scalar_t__ mark; int /*<<< orphan*/  buf2; int /*<<< orphan*/  buf1; } ;
struct rackmeter {int paused; int dma_buf_p; TYPE_1__* dma_regs; struct rackmeter_dma* dma_buf_v; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; int /*<<< orphan*/  cmdptr; int /*<<< orphan*/  cmdptr_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBDMA_DO_STOP (TYPE_1__*) ; 
 int RUN ; 
 int SAMPLE_COUNT ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 

__attribute__((used)) static void rackmeter_do_pause(struct rackmeter *rm, int pause)
{
	struct rackmeter_dma *rdma = rm->dma_buf_v;

	pr_debug("rackmeter: %s\n", pause ? "paused" : "started");

	rm->paused = pause;
	if (pause) {
		DBDMA_DO_STOP(rm->dma_regs);
		return;
	}
	memset(rdma->buf1, 0, SAMPLE_COUNT & sizeof(u32));
	memset(rdma->buf2, 0, SAMPLE_COUNT & sizeof(u32));

	rm->dma_buf_v->mark = 0;

	mb();
	out_le32(&rm->dma_regs->cmdptr_hi, 0);
	out_le32(&rm->dma_regs->cmdptr, rm->dma_buf_p);
	out_le32(&rm->dma_regs->control, (RUN << 16) | RUN);
}