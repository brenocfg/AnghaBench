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
typedef  int uint16_t ;
struct enc_private {int /*<<< orphan*/  (* SetEnable ) (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ResetCapFlags ) (struct comedi_device*,struct enc_private*) ;int /*<<< orphan*/  (* SetIntSrc ) (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetMode ) (struct comedi_device*,struct enc_private*,int,int /*<<< orphan*/ ) ;} ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int BF_CLKENAB ; 
 int BF_CLKMULT ; 
 int BF_CLKPOL ; 
 int BF_CLKSRC ; 
 int BF_INDXSRC ; 
 int BF_LOADSRC ; 
 int /*<<< orphan*/  CLKENAB_ALWAYS ; 
 int CLKENAB_INDEX ; 
 int CLKMULT_1X ; 
 int CLKPOL_POS ; 
 int CLKSRC_COUNTER ; 
 int CNTDIR_UP ; 
 int /*<<< orphan*/  DEBUG (char*) ; 
 int INDXSRC_SOFT ; 
 int LOADSRC_INDX ; 
 int S626_ENCODER_CHANNELS ; 
 int /*<<< orphan*/  TRUE ; 
 struct enc_private* encpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,struct enc_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,struct enc_private*) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CountersInit(struct comedi_device *dev)
{
	int chan;
	struct enc_private *k;
	uint16_t Setup = (LOADSRC_INDX << BF_LOADSRC) |	/*  Preload upon */
	    /*  index. */
	    (INDXSRC_SOFT << BF_INDXSRC) |	/*  Disable hardware index. */
	    (CLKSRC_COUNTER << BF_CLKSRC) |	/*  Operating mode is counter. */
	    (CLKPOL_POS << BF_CLKPOL) |	/*  Active high clock. */
	    (CNTDIR_UP << BF_CLKPOL) |	/*  Count direction is up. */
	    (CLKMULT_1X << BF_CLKMULT) |	/*  Clock multiplier is 1x. */
	    (CLKENAB_INDEX << BF_CLKENAB);	/*  Enabled by index */

	/*  Disable all counter interrupts and clear any captured counter events. */
	for (chan = 0; chan < S626_ENCODER_CHANNELS; chan++) {
		k = &encpriv[chan];
		k->SetMode(dev, k, Setup, TRUE);
		k->SetIntSrc(dev, k, 0);
		k->ResetCapFlags(dev, k);
		k->SetEnable(dev, k, CLKENAB_ALWAYS);
	}
	DEBUG("CountersInit: counters initialized \n");

}