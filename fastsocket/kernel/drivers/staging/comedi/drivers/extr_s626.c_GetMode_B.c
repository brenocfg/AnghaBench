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
struct enc_private {int /*<<< orphan*/  MyCRB; int /*<<< orphan*/  MyCRA; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int CLKSRC_COUNTER ; 
 int CLKSRC_EXTENDER ; 
 int CLKSRC_TIMER ; 
 int CRABIT_CLKSRC_B ; 
 int CRABIT_INDXSRC_B ; 
 int CRBBIT_CLKENAB_B ; 
 int CRBBIT_CLKMULT_B ; 
 int CRBBIT_CLKPOL_B ; 
 int CRBBIT_INDXPOL_B ; 
 int CRBBIT_INTSRC_B ; 
 int CRBBIT_LATCHSRC ; 
 int CRBBIT_LOADSRC_B ; 
 int CRBMSK_CLKMULT_B ; 
 int DEBIread (struct comedi_device*,int /*<<< orphan*/ ) ; 
 int MULT_X0 ; 
 int MULT_X1 ; 
 int STDBIT_CLKENAB ; 
 int STDBIT_CLKMULT ; 
 int STDBIT_CLKPOL ; 
 int STDBIT_CLKSRC ; 
 int STDBIT_INDXPOL ; 
 int STDBIT_INDXSRC ; 
 int STDBIT_INTSRC ; 
 int STDBIT_LATCHSRC ; 
 int STDBIT_LOADSRC ; 
 int STDMSK_CLKENAB ; 
 int STDMSK_CLKMULT ; 
 int STDMSK_CLKPOL ; 
 int STDMSK_INDXPOL ; 
 int STDMSK_INDXSRC ; 
 int STDMSK_INTSRC ; 
 int STDMSK_LATCHSRC ; 
 int STDMSK_LOADSRC ; 

__attribute__((used)) static uint16_t GetMode_B(struct comedi_device *dev, struct enc_private *k)
{
	register uint16_t cra;
	register uint16_t crb;
	register uint16_t setup;

	/*  Fetch CRA and CRB register images. */
	cra = DEBIread(dev, k->MyCRA);
	crb = DEBIread(dev, k->MyCRB);

	/*  Populate the standardized counter setup bit fields.  Note: */
	/*  IndexSrc is restricted to ENC_X or IndxPol. */
	setup = (((crb << (STDBIT_INTSRC - CRBBIT_INTSRC_B)) & STDMSK_INTSRC)	/*  IntSrc   = IntSrcB. */
		 |((crb << (STDBIT_LATCHSRC - CRBBIT_LATCHSRC)) & STDMSK_LATCHSRC)	/*  LatchSrc = LatchSrcB. */
		 |((crb << (STDBIT_LOADSRC - CRBBIT_LOADSRC_B)) & STDMSK_LOADSRC)	/*  LoadSrc  = LoadSrcB. */
		 |((crb << (STDBIT_INDXPOL - CRBBIT_INDXPOL_B)) & STDMSK_INDXPOL)	/*  IndxPol  = IndxPolB. */
		 |((crb >> (CRBBIT_CLKENAB_B - STDBIT_CLKENAB)) & STDMSK_CLKENAB)	/*  ClkEnab  = ClkEnabB. */
		 |((cra >> ((CRABIT_INDXSRC_B + 1) - STDBIT_INDXSRC)) & STDMSK_INDXSRC));	/*  IndxSrc  = IndxSrcB<1>. */

	/*  Adjust mode-dependent parameters. */
	if ((crb & CRBMSK_CLKMULT_B) == (MULT_X0 << CRBBIT_CLKMULT_B))	/*  If Extender mode (ClkMultB == MULT_X0): */
		setup |= ((CLKSRC_EXTENDER << STDBIT_CLKSRC)	/*    Indicate Extender mode. */
			  |(MULT_X1 << STDBIT_CLKMULT)	/*    Indicate multiplier is 1x. */
			  |((cra >> (CRABIT_CLKSRC_B - STDBIT_CLKPOL)) & STDMSK_CLKPOL));	/*    Set ClkPol equal to Timer count direction (ClkSrcB<0>). */

	else if (cra & (2 << CRABIT_CLKSRC_B))	/*  If Timer mode (ClkSrcB<1> == 1): */
		setup |= ((CLKSRC_TIMER << STDBIT_CLKSRC)	/*    Indicate Timer mode. */
			  |(MULT_X1 << STDBIT_CLKMULT)	/*    Indicate multiplier is 1x. */
			  |((cra >> (CRABIT_CLKSRC_B - STDBIT_CLKPOL)) & STDMSK_CLKPOL));	/*    Set ClkPol equal to Timer count direction (ClkSrcB<0>). */

	else			/*  If Counter mode (ClkSrcB<1> == 0): */
		setup |= ((CLKSRC_COUNTER << STDBIT_CLKSRC)	/*    Indicate Timer mode. */
			  |((crb >> (CRBBIT_CLKMULT_B - STDBIT_CLKMULT)) & STDMSK_CLKMULT)	/*    Clock multiplier is passed through. */
			  |((crb << (STDBIT_CLKPOL - CRBBIT_CLKPOL_B)) & STDMSK_CLKPOL));	/*    Clock polarity is passed through. */

	/*  Return adjusted counter setup. */
	return setup;
}