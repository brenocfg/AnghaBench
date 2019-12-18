#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int reset; int /*<<< orphan*/  address; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ length; int cmd_count; int flags; scalar_t__ kernel_data; scalar_t__* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_READ ; 
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 TYPE_3__* FDCS ; 
 int FD_RAW_READ ; 
 unsigned long claim_dma_lock () ; 
 TYPE_2__* cont ; 
 int /*<<< orphan*/  fd_cacheflush (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fd_clear_dma_ff () ; 
 int /*<<< orphan*/  fd_disable_dma () ; 
 scalar_t__ fd_dma_setup (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fd_enable_dma () ; 
 int /*<<< orphan*/  fd_set_dma_addr (scalar_t__) ; 
 int /*<<< orphan*/  fd_set_dma_count (scalar_t__) ; 
 int /*<<< orphan*/  fd_set_dma_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floppy_disable_hlt () ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 TYPE_1__* raw_cmd ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtual_dma_port ; 

__attribute__((used)) static void setup_DMA(void)
{
	unsigned long f;

#ifdef FLOPPY_SANITY_CHECK
	if (raw_cmd->length == 0) {
		int i;

		printk("zero dma transfer size:");
		for (i = 0; i < raw_cmd->cmd_count; i++)
			printk("%x,", raw_cmd->cmd[i]);
		printk("\n");
		cont->done(0);
		FDCS->reset = 1;
		return;
	}
	if (((unsigned long)raw_cmd->kernel_data) % 512) {
		printk("non aligned address: %p\n", raw_cmd->kernel_data);
		cont->done(0);
		FDCS->reset = 1;
		return;
	}
#endif
	f = claim_dma_lock();
	fd_disable_dma();
#ifdef fd_dma_setup
	if (fd_dma_setup(raw_cmd->kernel_data, raw_cmd->length,
			 (raw_cmd->flags & FD_RAW_READ) ?
			 DMA_MODE_READ : DMA_MODE_WRITE, FDCS->address) < 0) {
		release_dma_lock(f);
		cont->done(0);
		FDCS->reset = 1;
		return;
	}
	release_dma_lock(f);
#else
	fd_clear_dma_ff();
	fd_cacheflush(raw_cmd->kernel_data, raw_cmd->length);
	fd_set_dma_mode((raw_cmd->flags & FD_RAW_READ) ?
			DMA_MODE_READ : DMA_MODE_WRITE);
	fd_set_dma_addr(raw_cmd->kernel_data);
	fd_set_dma_count(raw_cmd->length);
	virtual_dma_port = FDCS->address;
	fd_enable_dma();
	release_dma_lock(f);
#endif
	floppy_disable_hlt();
}