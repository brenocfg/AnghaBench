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
 int CLKSRC_TIMER ; 
 int CRABIT_CLKMULT_A ; 
 int CRABIT_CLKPOL_A ; 
 int CRABIT_CLKSRC_A ; 
 int CRABIT_INDXPOL_A ; 
 int CRABIT_INDXSRC_A ; 
 int CRABIT_INTSRC_A ; 
 int CRAMSK_CLKMULT_A ; 
 int CRBBIT_CLKENAB_A ; 
 int CRBBIT_LATCHSRC ; 
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
 int STDMSK_CLKENAB ; 
 int STDMSK_CLKMULT ; 
 int STDMSK_CLKPOL ; 
 int STDMSK_INDXPOL ; 
 int STDMSK_INDXSRC ; 
 int STDMSK_INTSRC ; 
 int STDMSK_LATCHSRC ; 
 int STDMSK_LOADSRC ; 

__attribute__((used)) static uint16_t GetMode_A(struct comedi_device *dev, struct enc_private *k)
{
	register uint16_t cra;
	register uint16_t crb;
	register uint16_t setup;

	/*  Fetch CRA and CRB register images. */
	cra = DEBIread(dev, k->MyCRA);
	crb = DEBIread(dev, k->MyCRB);

	/*  Populate the standardized counter setup bit fields.  Note: */
	/*  IndexSrc is restricted to ENC_X or IndxPol. */
	setup = ((cra & STDMSK_LOADSRC)	/*  LoadSrc  = LoadSrcA. */
		 |((crb << (STDBIT_LATCHSRC - CRBBIT_LATCHSRC)) & STDMSK_LATCHSRC)	/*  LatchSrc = LatchSrcA. */
		 |((cra << (STDBIT_INTSRC - CRABIT_INTSRC_A)) & STDMSK_INTSRC)	/*  IntSrc   = IntSrcA. */
		 |((cra << (STDBIT_INDXSRC - (CRABIT_INDXSRC_A + 1))) & STDMSK_INDXSRC)	/*  IndxSrc  = IndxSrcA<1>. */
		 |((cra >> (CRABIT_INDXPOL_A - STDBIT_INDXPOL)) & STDMSK_INDXPOL)	/*  IndxPol  = IndxPolA. */
		 |((crb >> (CRBBIT_CLKENAB_A - STDBIT_CLKENAB)) & STDMSK_CLKENAB));	/*  ClkEnab  = ClkEnabA. */

	/*  Adjust mode-dependent parameters. */
	if (cra & (2 << CRABIT_CLKSRC_A))	/*  If Timer mode (ClkSrcA<1> == 1): */
		setup |= ((CLKSRC_TIMER << STDBIT_CLKSRC)	/*    Indicate Timer mode. */
			  |((cra << (STDBIT_CLKPOL - CRABIT_CLKSRC_A)) & STDMSK_CLKPOL)	/*    Set ClkPol to indicate count direction (ClkSrcA<0>). */
			  |(MULT_X1 << STDBIT_CLKMULT));	/*    ClkMult must be 1x in Timer mode. */

	else			/*  If Counter mode (ClkSrcA<1> == 0): */
		setup |= ((CLKSRC_COUNTER << STDBIT_CLKSRC)	/*    Indicate Counter mode. */
			  |((cra >> (CRABIT_CLKPOL_A - STDBIT_CLKPOL)) & STDMSK_CLKPOL)	/*    Pass through ClkPol. */
			  |(((cra & CRAMSK_CLKMULT_A) == (MULT_X0 << CRABIT_CLKMULT_A)) ?	/*    Force ClkMult to 1x if not legal, else pass through. */
			    (MULT_X1 << STDBIT_CLKMULT) :
			    ((cra >> (CRABIT_CLKMULT_A -
				      STDBIT_CLKMULT)) & STDMSK_CLKMULT)));

	/*  Return adjusted counter setup. */
	return setup;
}