#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tifm_ms {int use_dma; unsigned int mode_mask; TYPE_1__* req; scalar_t__ timeout_jiffies; int /*<<< orphan*/  timer; scalar_t__ cmd_flags; scalar_t__ io_word; scalar_t__ io_pos; scalar_t__ block_pos; struct tifm_dev* dev; } ;
struct tifm_dev {int /*<<< orphan*/  dev; scalar_t__ addr; } ;
struct TYPE_6__ {unsigned int length; } ;
struct TYPE_5__ {unsigned char* data; unsigned int data_len; scalar_t__ data_dir; int error; int tpc; TYPE_2__ sg; scalar_t__ long_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 scalar_t__ READ ; 
 scalar_t__ SOCK_CONTROL ; 
 scalar_t__ SOCK_DMA_ADDRESS ; 
 scalar_t__ SOCK_DMA_CONTROL ; 
 scalar_t__ SOCK_DMA_FIFO_INT_ENABLE_CLEAR ; 
 scalar_t__ SOCK_DMA_FIFO_INT_ENABLE_SET ; 
 scalar_t__ SOCK_FIFO_CONTROL ; 
 scalar_t__ SOCK_FIFO_PAGE_SIZE ; 
 scalar_t__ SOCK_MS_COMMAND ; 
 scalar_t__ SOCK_MS_SYSTEM ; 
 unsigned int TIFM_CTRL_LED ; 
 int TIFM_DMA_EN ; 
 unsigned int TIFM_DMA_TX ; 
 unsigned int TIFM_FIFO_ENABLE ; 
 unsigned int TIFM_FIFO_INTMASK ; 
 unsigned int TIFM_FIFO_INT_SETALL ; 
 unsigned int TIFM_FIFO_MORE ; 
 unsigned int TIFM_MS_SYS_DMA ; 
 unsigned int TIFM_MS_SYS_FIFO ; 
 unsigned int TIFM_MS_SYS_INTCLR ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 unsigned int ilog2 (unsigned int) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  no_dma ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int sg_dma_address (TYPE_2__*) ; 
 unsigned int sg_dma_len (TYPE_2__*) ; 
 int tifm_map_sg (struct tifm_dev*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int tifm_ms_issue_cmd(struct tifm_ms *host)
{
	struct tifm_dev *sock = host->dev;
	unsigned char *data;
	unsigned int data_len, cmd, sys_param;

	host->cmd_flags = 0;
	host->block_pos = 0;
	host->io_pos = 0;
	host->io_word = 0;
	host->cmd_flags = 0;

	data = host->req->data;

	host->use_dma = !no_dma;

	if (host->req->long_data) {
		data_len = host->req->sg.length;
		if (!is_power_of_2(data_len))
			host->use_dma = 0;
	} else {
		data_len = host->req->data_len;
		host->use_dma = 0;
	}

	writel(TIFM_FIFO_INT_SETALL,
	       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_CLEAR);
	writel(TIFM_FIFO_ENABLE,
	       sock->addr + SOCK_FIFO_CONTROL);

	if (host->use_dma) {
		if (1 != tifm_map_sg(sock, &host->req->sg, 1,
				     host->req->data_dir == READ
				     ? PCI_DMA_FROMDEVICE
				     : PCI_DMA_TODEVICE)) {
			host->req->error = -ENOMEM;
			return host->req->error;
		}
		data_len = sg_dma_len(&host->req->sg);

		writel(ilog2(data_len) - 2,
		       sock->addr + SOCK_FIFO_PAGE_SIZE);
		writel(TIFM_FIFO_INTMASK,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
		sys_param = TIFM_DMA_EN | (1 << 8);
		if (host->req->data_dir == WRITE)
			sys_param |= TIFM_DMA_TX;

		writel(TIFM_FIFO_INTMASK,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);

		writel(sg_dma_address(&host->req->sg),
		       sock->addr + SOCK_DMA_ADDRESS);
		writel(sys_param, sock->addr + SOCK_DMA_CONTROL);
	} else {
		writel(host->mode_mask | TIFM_MS_SYS_FIFO,
		       sock->addr + SOCK_MS_SYSTEM);

		writel(TIFM_FIFO_MORE,
		       sock->addr + SOCK_DMA_FIFO_INT_ENABLE_SET);
	}

	mod_timer(&host->timer, jiffies + host->timeout_jiffies);
	writel(TIFM_CTRL_LED | readl(sock->addr + SOCK_CONTROL),
	       sock->addr + SOCK_CONTROL);
	host->req->error = 0;

	sys_param = readl(sock->addr + SOCK_MS_SYSTEM);
	sys_param |= TIFM_MS_SYS_INTCLR;

	if (host->use_dma)
		sys_param |= TIFM_MS_SYS_DMA;
	else
		sys_param &= ~TIFM_MS_SYS_DMA;

	writel(sys_param, sock->addr + SOCK_MS_SYSTEM);

	cmd = (host->req->tpc & 0xf) << 12;
	cmd |= data_len;
	writel(cmd, sock->addr + SOCK_MS_COMMAND);

	dev_dbg(&sock->dev, "executing TPC %x, %x\n", cmd, sys_param);
	return 0;
}