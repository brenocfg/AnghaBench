#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wb35_reg {int M28_MacControl; } ;
struct hw_data {int Channel; int band; scalar_t__ SurpriseRemove; struct wb35_reg reg; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_4__ {int band; int ChanNo; } ;
typedef  TYPE_1__ ChanInfo ;

/* Variables and functions */
 int /*<<< orphan*/  RFSynthesizer_SwitchingChannel (struct hw_data*,TYPE_1__) ; 
 int /*<<< orphan*/  Wb35Reg_WriteWithCallbackValue (struct hw_data*,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 

__attribute__((used)) static void
hal_set_current_channel_ex(struct hw_data *pHwData, ChanInfo channel)
{
	struct wb35_reg *reg = &pHwData->reg;

	if (pHwData->SurpriseRemove)
		return;

	printk("Going to channel: %d/%d\n", channel.band, channel.ChanNo);

	RFSynthesizer_SwitchingChannel(pHwData, channel);	// Switch channel
	pHwData->Channel = channel.ChanNo;
	pHwData->band = channel.band;
#ifdef _PE_STATE_DUMP_
	printk("Set channel is %d, band =%d\n", pHwData->Channel,
	       pHwData->band);
#endif
	reg->M28_MacControl &= ~0xff;	// Clean channel information field
	reg->M28_MacControl |= channel.ChanNo;
	Wb35Reg_WriteWithCallbackValue(pHwData, 0x0828, reg->M28_MacControl,
				       (s8 *) & channel, sizeof(ChanInfo));
}