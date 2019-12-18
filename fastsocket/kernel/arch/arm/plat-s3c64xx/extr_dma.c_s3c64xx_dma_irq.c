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
struct s3c64xx_dmac {scalar_t__ regs; struct s3c2410_dma_chan* channels; } ;
struct s3c64xx_dma_buff {struct s3c64xx_dma_buff* next; } ;
struct s3c2410_dma_chan {int flags; struct s3c64xx_dma_buff* next; struct s3c64xx_dma_buff* end; struct s3c64xx_dma_buff* curr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum s3c2410_dma_buffresult { ____Placeholder_s3c2410_dma_buffresult } s3c2410_dma_buffresult ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PL080_ERR_CLEAR ; 
 scalar_t__ PL080_ERR_STATUS ; 
 scalar_t__ PL080_TC_CLEAR ; 
 scalar_t__ PL080_TC_STATUS ; 
 int S3C2410_DMAF_CIRCULAR ; 
 int S3C2410_RES_ERR ; 
 int S3C2410_RES_OK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c64xx_dma_bufffdone (struct s3c2410_dma_chan*,struct s3c64xx_dma_buff*,int) ; 
 int /*<<< orphan*/  s3c64xx_dma_freebuff (struct s3c64xx_dma_buff*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t s3c64xx_dma_irq(int irq, void *pw)
{
	struct s3c64xx_dmac *dmac = pw;
	struct s3c2410_dma_chan *chan;
	enum s3c2410_dma_buffresult res;
	u32 tcstat, errstat;
	u32 bit;
	int offs;

	tcstat = readl(dmac->regs + PL080_TC_STATUS);
	errstat = readl(dmac->regs + PL080_ERR_STATUS);

	for (offs = 0, bit = 1; offs < 8; offs++, bit <<= 1) {
		struct s3c64xx_dma_buff *buff;

		if (!(errstat & bit) && !(tcstat & bit))
			continue;

		chan = dmac->channels + offs;
		res = S3C2410_RES_ERR;

		if (tcstat & bit) {
			writel(bit, dmac->regs + PL080_TC_CLEAR);
			res = S3C2410_RES_OK;
		}

		if (errstat & bit)
			writel(bit, dmac->regs + PL080_ERR_CLEAR);

		/* 'next' points to the buffer that is next to the
		 * currently active buffer.
		 * For CIRCULAR queues, 'next' will be same as 'curr'
		 * when 'end' is the active buffer.
		 */
		buff = chan->curr;
		while (buff && buff != chan->next
				&& buff->next != chan->next)
			buff = buff->next;

		if (!buff)
			BUG();

		if (buff == chan->next)
			buff = chan->end;

		s3c64xx_dma_bufffdone(chan, buff, res);

		/* Free the node and update curr, if non-circular queue */
		if (!(chan->flags & S3C2410_DMAF_CIRCULAR)) {
			chan->curr = buff->next;
			s3c64xx_dma_freebuff(buff);
		}

		/* Update 'next' */
		buff = chan->next;
		if (chan->next == chan->end) {
			chan->next = chan->curr;
			if (!(chan->flags & S3C2410_DMAF_CIRCULAR))
				chan->end = NULL;
		} else {
			chan->next = buff->next;
		}
	}

	return IRQ_HANDLED;
}