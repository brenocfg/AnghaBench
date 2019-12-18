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
struct enc_private {int /*<<< orphan*/  (* SetIntSrc ) (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* SetLoadTrig ) (struct comedi_device*,struct enc_private*,int) ;int /*<<< orphan*/  (* PulseIndex ) (struct comedi_device*,struct enc_private*) ;int /*<<< orphan*/  (* SetMode ) (struct comedi_device*,struct enc_private*,int,int /*<<< orphan*/ ) ;} ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int BF_CLKENAB ; 
 int BF_CLKMULT ; 
 int BF_CLKPOL ; 
 int BF_CLKSRC ; 
 int BF_INDXSRC ; 
 int BF_LOADSRC ; 
 int CLKENAB_INDEX ; 
 int CLKMULT_1X ; 
 int CLKPOL_POS ; 
 int CLKSRC_TIMER ; 
 int CNTDIR_DOWN ; 
 int /*<<< orphan*/  FALSE ; 
 int INDXSRC_SOFT ; 
 int /*<<< orphan*/  INTSRC_OVER ; 
 int LATCHSRC_A_INDXA ; 
 int LOADSRC_INDX ; 
 int /*<<< orphan*/  Preload (struct comedi_device*,struct enc_private*,int) ; 
 int /*<<< orphan*/  SetLatchSource (struct comedi_device*,struct enc_private*,int) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,struct enc_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,struct enc_private*,int) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,struct enc_private*) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,struct enc_private*,int) ; 
 int /*<<< orphan*/  stub5 (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s626_timer_load(struct comedi_device *dev, struct enc_private *k,
			    int tick)
{
	uint16_t Setup = (LOADSRC_INDX << BF_LOADSRC) |	/*  Preload upon */
	    /*  index. */
	    (INDXSRC_SOFT << BF_INDXSRC) |	/*  Disable hardware index. */
	    (CLKSRC_TIMER << BF_CLKSRC) |	/*  Operating mode is Timer. */
	    (CLKPOL_POS << BF_CLKPOL) |	/*  Active high clock. */
	    (CNTDIR_DOWN << BF_CLKPOL) |	/*  Count direction is Down. */
	    (CLKMULT_1X << BF_CLKMULT) |	/*  Clock multiplier is 1x. */
	    (CLKENAB_INDEX << BF_CLKENAB);
	uint16_t valueSrclatch = LATCHSRC_A_INDXA;
	/*   uint16_t enab=CLKENAB_ALWAYS; */

	k->SetMode(dev, k, Setup, FALSE);

	/*  Set the preload register */
	Preload(dev, k, tick);

	/*  Software index pulse forces the preload register to load */
	/*  into the counter */
	k->SetLoadTrig(dev, k, 0);
	k->PulseIndex(dev, k);

	/* set reload on counter overflow */
	k->SetLoadTrig(dev, k, 1);

	/* set interrupt on overflow */
	k->SetIntSrc(dev, k, INTSRC_OVER);

	SetLatchSource(dev, k, valueSrclatch);
	/*   k->SetEnable(dev,k,(uint16_t)(enab != 0)); */
}