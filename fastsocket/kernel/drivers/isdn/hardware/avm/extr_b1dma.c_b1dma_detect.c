#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int csr; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ avmcard ;

/* Variables and functions */
 int /*<<< orphan*/  AMCC_INTCSR ; 
 int /*<<< orphan*/  AMCC_MCSR ; 
 int /*<<< orphan*/  AMCC_RXLEN ; 
 int /*<<< orphan*/  AMCC_RXPTR ; 
 int /*<<< orphan*/  AMCC_TXLEN ; 
 int /*<<< orphan*/  AMCC_TXPTR ; 
 int b1dma_readl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b1dma_writel (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int t1inp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t1outp (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int b1dma_detect(avmcard *card)
{
	b1dma_writel(card, 0, AMCC_MCSR);
	mdelay(10);
	b1dma_writel(card, 0x0f000000, AMCC_MCSR); /* reset all */
	mdelay(10);
	b1dma_writel(card, 0, AMCC_MCSR);
	mdelay(42);

	b1dma_writel(card, 0, AMCC_RXLEN);
	b1dma_writel(card, 0, AMCC_TXLEN);
	card->csr = 0x0;
	b1dma_writel(card, card->csr, AMCC_INTCSR);

	if (b1dma_readl(card, AMCC_MCSR) != 0x000000E6)
		return 1;

	b1dma_writel(card, 0xffffffff, AMCC_RXPTR);
	b1dma_writel(card, 0xffffffff, AMCC_TXPTR);
	if (   b1dma_readl(card, AMCC_RXPTR) != 0xfffffffc
	    || b1dma_readl(card, AMCC_TXPTR) != 0xfffffffc)
		return 2;

	b1dma_writel(card, 0x0, AMCC_RXPTR);
	b1dma_writel(card, 0x0, AMCC_TXPTR);
	if (   b1dma_readl(card, AMCC_RXPTR) != 0x0
	    || b1dma_readl(card, AMCC_TXPTR) != 0x0)
		return 3;

	t1outp(card->port, 0x10, 0x00);
	t1outp(card->port, 0x07, 0x00);
	
	t1outp(card->port, 0x02, 0x02);
	t1outp(card->port, 0x03, 0x02);

	if (   (t1inp(card->port, 0x02) & 0xFE) != 0x02
	    || t1inp(card->port, 0x3) != 0x03)
		return 4;

	t1outp(card->port, 0x02, 0x00);
	t1outp(card->port, 0x03, 0x00);

	if (   (t1inp(card->port, 0x02) & 0xFE) != 0x00
	    || t1inp(card->port, 0x3) != 0x01)
		return 5;

	return 0;
}