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
struct TYPE_2__ {struct mcp_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mcp_sa11x0 {int dummy; } ;
struct mcp_plat_data {int sclk_rate; int mccr0; int /*<<< orphan*/  mccr1; } ;
struct mcp {int sclk_rate; int rw_timeout; int /*<<< orphan*/  dma_telco_wr; int /*<<< orphan*/  dma_telco_rd; int /*<<< orphan*/  dma_audio_wr; int /*<<< orphan*/  dma_audio_rd; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSABET_BCR_CODEC_RST ; 
 int /*<<< orphan*/  ASSABET_BCR_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_Ser4MCP0Rd ; 
 int /*<<< orphan*/  DMA_Ser4MCP0Wr ; 
 int /*<<< orphan*/  DMA_Ser4MCP1Rd ; 
 int /*<<< orphan*/  DMA_Ser4MCP1Wr ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int PPC_RXD4 ; 
 int PPC_SCLK ; 
 int PPC_SFRM ; 
 int PPC_TXD4 ; 
 int PPDR ; 
 int PPSR ; 
 int PSDR ; 
 int Ser4MCCR0 ; 
 int /*<<< orphan*/  Ser4MCCR1 ; 
 int Ser4MCSR ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ machine_is_assabet () ; 
 struct mcp* mcp_host_alloc (TYPE_1__*,int) ; 
 int mcp_host_register (struct mcp*) ; 
 int /*<<< orphan*/  mcp_sa11x0 ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mcp*) ; 
 int /*<<< orphan*/  release_mem_region (int,int) ; 
 int /*<<< orphan*/  request_mem_region (int,int,char*) ; 

__attribute__((used)) static int mcp_sa11x0_probe(struct platform_device *pdev)
{
	struct mcp_plat_data *data = pdev->dev.platform_data;
	struct mcp *mcp;
	int ret;

	if (!data)
		return -ENODEV;

	if (!request_mem_region(0x80060000, 0x60, "sa11x0-mcp"))
		return -EBUSY;

	mcp = mcp_host_alloc(&pdev->dev, sizeof(struct mcp_sa11x0));
	if (!mcp) {
		ret = -ENOMEM;
		goto release;
	}

	mcp->owner		= THIS_MODULE;
	mcp->ops		= &mcp_sa11x0;
	mcp->sclk_rate		= data->sclk_rate;
	mcp->dma_audio_rd	= DMA_Ser4MCP0Rd;
	mcp->dma_audio_wr	= DMA_Ser4MCP0Wr;
	mcp->dma_telco_rd	= DMA_Ser4MCP1Rd;
	mcp->dma_telco_wr	= DMA_Ser4MCP1Wr;

	platform_set_drvdata(pdev, mcp);

	if (machine_is_assabet()) {
		ASSABET_BCR_set(ASSABET_BCR_CODEC_RST);
	}

	/*
	 * Setup the PPC unit correctly.
	 */
	PPDR &= ~PPC_RXD4;
	PPDR |= PPC_TXD4 | PPC_SCLK | PPC_SFRM;
	PSDR |= PPC_RXD4;
	PSDR &= ~(PPC_TXD4 | PPC_SCLK | PPC_SFRM);
	PPSR &= ~(PPC_TXD4 | PPC_SCLK | PPC_SFRM);

	/*
	 * Initialise device.  Note that we initially
	 * set the sampling rate to minimum.
	 */
	Ser4MCSR = -1;
	Ser4MCCR1 = data->mccr1;
	Ser4MCCR0 = data->mccr0 | 0x7f7f;

	/*
	 * Calculate the read/write timeout (us) from the bit clock
	 * rate.  This is the period for 3 64-bit frames.  Always
	 * round this time up.
	 */
	mcp->rw_timeout = (64 * 3 * 1000000 + mcp->sclk_rate - 1) /
			  mcp->sclk_rate;

	ret = mcp_host_register(mcp);
	if (ret == 0)
		goto out;

 release:
	release_mem_region(0x80060000, 0x60);
	platform_set_drvdata(pdev, NULL);

 out:
	return ret;
}