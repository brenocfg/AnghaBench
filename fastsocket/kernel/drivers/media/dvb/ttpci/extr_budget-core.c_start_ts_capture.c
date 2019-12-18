#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct saa7146_dev {int dummy; } ;
struct TYPE_4__ {int dma; } ;
struct budget {int buffer_size; int buffer_height; int buffer_width; struct saa7146_dev* dev; TYPE_2__ pt; int /*<<< orphan*/  video_port; TYPE_1__* card; scalar_t__ ttbp; int /*<<< orphan*/  grabbing; int /*<<< orphan*/  fe_synced; int /*<<< orphan*/  feeding; } ;
struct TYPE_3__ {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_EVEN3 ; 
 int /*<<< orphan*/  BASE_ODD3 ; 
 int /*<<< orphan*/  BASE_PAGE3 ; 
 int /*<<< orphan*/  BRS_CTRL ; 
#define  BUDGET_CIN1200C_MK3 132 
#define  BUDGET_FS_ACTIVY 131 
#define  BUDGET_KNC1CP_MK3 130 
#define  BUDGET_KNC1C_MK3 129 
#define  BUDGET_PATCH 128 
 int /*<<< orphan*/  BUDGET_VIDEO_PORTA ; 
 int /*<<< orphan*/  DD1_INIT ; 
 int MASK_04 ; 
 int MASK_08 ; 
 int MASK_09 ; 
 int MASK_10 ; 
 int MASK_20 ; 
 int MASK_24 ; 
 int MASK_25 ; 
 int MASK_26 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  MC2 ; 
 int ME1 ; 
 int /*<<< orphan*/  NUM_LINE_BYTE3 ; 
 int /*<<< orphan*/  PCI_BT_V1 ; 
 int /*<<< orphan*/  PITCH3 ; 
 int /*<<< orphan*/  PROT_ADDR3 ; 
 int /*<<< orphan*/  SAA7146_IER_ENABLE (struct saa7146_dev*,int) ; 
 int /*<<< orphan*/  SAA7146_ISR_CLEAR (struct saa7146_dev*,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int saa7146_read (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int start_ts_capture(struct budget *budget)
{
	struct saa7146_dev *dev = budget->dev;

	dprintk(2, "budget: %p\n", budget);

	if (!budget->feeding || !budget->fe_synced)
		return 0;

	saa7146_write(dev, MC1, MASK_20);	// DMA3 off

	memset(budget->grabbing, 0x00, budget->buffer_size);

	saa7146_write(dev, PCI_BT_V1, 0x001c0000 | (saa7146_read(dev, PCI_BT_V1) & ~0x001f0000));

	budget->ttbp = 0;

	/*
	 *  Signal path on the Activy:
	 *
	 *  tuner -> SAA7146 port A -> SAA7146 BRS -> SAA7146 DMA3 -> memory
	 *
	 *  Since the tuner feeds 204 bytes packets into the SAA7146,
	 *  DMA3 is configured to strip the trailing 16 FEC bytes:
	 *      Pitch: 188, NumBytes3: 188, NumLines3: 1024
	 */

	switch(budget->card->type) {
	case BUDGET_FS_ACTIVY:
		saa7146_write(dev, DD1_INIT, 0x04000000);
		saa7146_write(dev, MC2, (MASK_09 | MASK_25));
		saa7146_write(dev, BRS_CTRL, 0x00000000);
		break;
	case BUDGET_PATCH:
		saa7146_write(dev, DD1_INIT, 0x00000200);
		saa7146_write(dev, MC2, (MASK_10 | MASK_26));
		saa7146_write(dev, BRS_CTRL, 0x60000000);
		break;
	case BUDGET_CIN1200C_MK3:
	case BUDGET_KNC1C_MK3:
	case BUDGET_KNC1CP_MK3:
		if (budget->video_port == BUDGET_VIDEO_PORTA) {
			saa7146_write(dev, DD1_INIT, 0x06000200);
			saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_write(dev, BRS_CTRL, 0x00000000);
		} else {
			saa7146_write(dev, DD1_INIT, 0x00000600);
			saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_write(dev, BRS_CTRL, 0x60000000);
		}
		break;
	default:
		if (budget->video_port == BUDGET_VIDEO_PORTA) {
			saa7146_write(dev, DD1_INIT, 0x06000200);
			saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_write(dev, BRS_CTRL, 0x00000000);
		} else {
			saa7146_write(dev, DD1_INIT, 0x02000600);
			saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));
			saa7146_write(dev, BRS_CTRL, 0x60000000);
		}
	}

	saa7146_write(dev, MC2, (MASK_08 | MASK_24));
	mdelay(10);

	saa7146_write(dev, BASE_ODD3, 0);
	if (budget->buffer_size > budget->buffer_height * budget->buffer_width) {
		// using odd/even buffers
		saa7146_write(dev, BASE_EVEN3, budget->buffer_height * budget->buffer_width);
	} else {
		// using a single buffer
		saa7146_write(dev, BASE_EVEN3, 0);
	}
	saa7146_write(dev, PROT_ADDR3, budget->buffer_size);
	saa7146_write(dev, BASE_PAGE3, budget->pt.dma | ME1 | 0x90);

	saa7146_write(dev, PITCH3, budget->buffer_width);
	saa7146_write(dev, NUM_LINE_BYTE3,
			(budget->buffer_height << 16) | budget->buffer_width);

	saa7146_write(dev, MC2, (MASK_04 | MASK_20));

	SAA7146_ISR_CLEAR(budget->dev, MASK_10);	/* VPE */
	SAA7146_IER_ENABLE(budget->dev, MASK_10);	/* VPE */
	saa7146_write(dev, MC1, (MASK_04 | MASK_20));	/* DMA3 on */

	return 0;
}