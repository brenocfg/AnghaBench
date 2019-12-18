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
typedef  scalar_t__ uint16_t ;
struct enc_private {int /*<<< orphan*/  (* SetEnable ) (struct comedi_device*,struct enc_private*,scalar_t__) ;int /*<<< orphan*/  (* PulseIndex ) (struct comedi_device*,struct enc_private*) ;int /*<<< orphan*/  (* SetMode ) (struct comedi_device*,struct enc_private*,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/ * data; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BF_CLKENAB ; 
 scalar_t__ BF_CLKMULT ; 
 scalar_t__ BF_CLKPOL ; 
 scalar_t__ BF_CLKSRC ; 
 scalar_t__ BF_INDXSRC ; 
 scalar_t__ BF_LOADSRC ; 
 scalar_t__ CLKENAB_ALWAYS ; 
 scalar_t__ CLKENAB_INDEX ; 
 scalar_t__ CLKMULT_1X ; 
 scalar_t__ CLKPOL_POS ; 
 scalar_t__ CLKSRC_COUNTER ; 
 size_t CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG (char*) ; 
 scalar_t__ INDXSRC_SOFT ; 
 scalar_t__ LATCHSRC_AB_READ ; 
 scalar_t__ LOADSRC_INDX ; 
 int /*<<< orphan*/  Preload (struct comedi_device*,struct enc_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLatchSource (struct comedi_device*,struct enc_private*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 struct enc_private* encpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,struct enc_private*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,struct enc_private*) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,struct enc_private*,scalar_t__) ; 

__attribute__((used)) static int s626_enc_insn_config(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	uint16_t Setup = (LOADSRC_INDX << BF_LOADSRC) |	/*  Preload upon */
	    /*  index. */
	    (INDXSRC_SOFT << BF_INDXSRC) |	/*  Disable hardware index. */
	    (CLKSRC_COUNTER << BF_CLKSRC) |	/*  Operating mode is Counter. */
	    (CLKPOL_POS << BF_CLKPOL) |	/*  Active high clock. */
	    /* ( CNTDIR_UP << BF_CLKPOL ) |      // Count direction is Down. */
	    (CLKMULT_1X << BF_CLKMULT) |	/*  Clock multiplier is 1x. */
	    (CLKENAB_INDEX << BF_CLKENAB);
	/*   uint16_t DisableIntSrc=TRUE; */
	/*  uint32_t Preloadvalue;              //Counter initial value */
	uint16_t valueSrclatch = LATCHSRC_AB_READ;
	uint16_t enab = CLKENAB_ALWAYS;
	struct enc_private *k = &encpriv[CR_CHAN(insn->chanspec)];

	DEBUG("s626_enc_insn_config: encoder config\n");

	/*   (data==NULL) ? (Preloadvalue=0) : (Preloadvalue=data[0]); */

	k->SetMode(dev, k, Setup, TRUE);
	Preload(dev, k, *(insn->data));
	k->PulseIndex(dev, k);
	SetLatchSource(dev, k, valueSrclatch);
	k->SetEnable(dev, k, (uint16_t) (enab != 0));

	return insn->n;
}