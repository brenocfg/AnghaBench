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
struct whcrc {int /*<<< orphan*/  rc_len; int /*<<< orphan*/  area; int /*<<< orphan*/  rc_base; int /*<<< orphan*/  cmd_dma_buf; int /*<<< orphan*/  cmd_buf; int /*<<< orphan*/  evt_dma_buf; int /*<<< orphan*/  evt_buf; struct umc_dev* umc_dev; } ;
struct umc_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct whcrc*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void whcrc_release_rc_umc(struct whcrc *whcrc)
{
	struct umc_dev *umc_dev = whcrc->umc_dev;

	dma_free_coherent(&umc_dev->dev, PAGE_SIZE, whcrc->evt_buf,
			  whcrc->evt_dma_buf);
	dma_free_coherent(&umc_dev->dev, PAGE_SIZE, whcrc->cmd_buf,
			  whcrc->cmd_dma_buf);
	free_irq(umc_dev->irq, whcrc);
	iounmap(whcrc->rc_base);
	release_mem_region(whcrc->area, whcrc->rc_len);
}