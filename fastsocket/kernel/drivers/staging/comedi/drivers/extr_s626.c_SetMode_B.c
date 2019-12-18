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
typedef  int uint16_t ;
struct enc_private {int /*<<< orphan*/  MyCRB; int /*<<< orphan*/  MyCRA; int /*<<< orphan*/ * MyEventBits; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  CounterIntEnabs; } ;

/* Variables and functions */
 int CLKSRC_COUNTER ; 
#define  CLKSRC_EXTENDER 129 
#define  CLKSRC_TIMER 128 
 int CRABIT_CLKSRC_B ; 
 int CRABIT_INDXSRC_B ; 
 int CRAMSK_CLKSRC_B ; 
 int CRAMSK_INDXSRC_B ; 
 int CRBBIT_CLKENAB_B ; 
 int CRBBIT_CLKMULT_B ; 
 int CRBBIT_CLKPOL_B ; 
 int CRBBIT_INDXPOL_B ; 
 int CRBBIT_INTSRC_B ; 
 int CRBBIT_LOADSRC_B ; 
 int CRBMSK_CLKENAB_A ; 
 int CRBMSK_INTRESETCMD ; 
 int CRBMSK_INTRESET_B ; 
 int CRBMSK_LATCHSRC ; 
 int /*<<< orphan*/  DEBIreplace (struct comedi_device*,int /*<<< orphan*/ ,int,int) ; 
 int MULT_X0 ; 
 int MULT_X1 ; 
 int STDBIT_CLKENAB ; 
 int STDBIT_CLKMULT ; 
 int STDBIT_CLKPOL ; 
 int STDBIT_CLKSRC ; 
 int STDBIT_INDXPOL ; 
 int STDBIT_INDXSRC ; 
 int STDBIT_INTSRC ; 
 int STDBIT_LOADSRC ; 
 int STDMSK_CLKENAB ; 
 int STDMSK_CLKMULT ; 
 int STDMSK_CLKPOL ; 
 int STDMSK_CLKSRC ; 
 int STDMSK_INDXPOL ; 
 int STDMSK_INDXSRC ; 
 int STDMSK_INTSRC ; 
 int STDMSK_LOADSRC ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static void SetMode_B(struct comedi_device *dev, struct enc_private *k,
		      uint16_t Setup, uint16_t DisableIntSrc)
{
	register uint16_t cra;
	register uint16_t crb;
	register uint16_t setup = Setup;	/*  Cache the Standard Setup. */

	/*  Initialize CRA and CRB images. */
	cra = ((setup & STDMSK_INDXSRC) << ((CRABIT_INDXSRC_B + 1) - STDBIT_INDXSRC));	/*  IndexSrc field is restricted to ENC_X or IndxPol. */

	crb = (CRBMSK_INTRESETCMD | CRBMSK_INTRESET_B	/*  Reset event captures and disable interrupts. */
	       | ((setup & STDMSK_CLKENAB) << (CRBBIT_CLKENAB_B - STDBIT_CLKENAB))	/*  Clock enable is passed through. */
	       |((setup & STDMSK_LOADSRC) >> (STDBIT_LOADSRC - CRBBIT_LOADSRC_B)));	/*  Preload trigger source is passed through. */

	/*  Force IntSrc to Disabled if DisableIntSrc is asserted. */
	if (!DisableIntSrc)
		crb |= ((setup & STDMSK_INTSRC) >> (STDBIT_INTSRC -
						    CRBBIT_INTSRC_B));

	/*  Populate all mode-dependent attributes of CRA & CRB images. */
	switch ((setup & STDMSK_CLKSRC) >> STDBIT_CLKSRC) {
	case CLKSRC_TIMER:	/*  Timer Mode: */
		cra |= ((2 << CRABIT_CLKSRC_B)	/*    ClkSrcB<1> selects system clock */
			|((setup & STDMSK_CLKPOL) << (CRABIT_CLKSRC_B - STDBIT_CLKPOL)));	/*      with direction (ClkSrcB<0>) obtained from ClkPol. */
		crb |= ((1 << CRBBIT_CLKPOL_B)	/*    ClkPolB behaves as always-on clock enable. */
			|(MULT_X1 << CRBBIT_CLKMULT_B));	/*    ClkMultB must be 1x. */
		break;

	case CLKSRC_EXTENDER:	/*  Extender Mode: */
		cra |= ((2 << CRABIT_CLKSRC_B)	/*    ClkSrcB source is OverflowA (same as "timer") */
			|((setup & STDMSK_CLKPOL) << (CRABIT_CLKSRC_B - STDBIT_CLKPOL)));	/*      with direction obtained from ClkPol. */
		crb |= ((1 << CRBBIT_CLKPOL_B)	/*    ClkPolB controls IndexB -- always set to active. */
			|(MULT_X0 << CRBBIT_CLKMULT_B));	/*    ClkMultB selects OverflowA as the clock source. */
		break;

	default:		/*  Counter Mode: */
		cra |= (CLKSRC_COUNTER << CRABIT_CLKSRC_B);	/*    Select ENC_C and ENC_D as clock/direction inputs. */
		crb |= (((setup & STDMSK_CLKPOL) >> (STDBIT_CLKPOL - CRBBIT_CLKPOL_B))	/*    ClkPol is passed through. */
			|(((setup & STDMSK_CLKMULT) == (MULT_X0 << STDBIT_CLKMULT)) ?	/*    Force ClkMult to x1 if not legal, otherwise pass through. */
			  (MULT_X1 << CRBBIT_CLKMULT_B) :
			  ((setup & STDMSK_CLKMULT) << (CRBBIT_CLKMULT_B -
							STDBIT_CLKMULT))));
	}

	/*  Force positive index polarity if IndxSrc is software-driven only, */
	/*  otherwise pass it through. */
	if (~setup & STDMSK_INDXSRC)
		crb |= ((setup & STDMSK_INDXPOL) >> (STDBIT_INDXPOL -
						     CRBBIT_INDXPOL_B));

	/*  If IntSrc has been forced to Disabled, update the MISC2 interrupt */
	/*  enable mask to indicate the counter interrupt is disabled. */
	if (DisableIntSrc)
		devpriv->CounterIntEnabs &= ~k->MyEventBits[3];

	/*  While retaining CounterA and LatchSrc configurations, program the */
	/*  new counter operating mode. */
	DEBIreplace(dev, k->MyCRA,
		    (uint16_t) (~(CRAMSK_INDXSRC_B | CRAMSK_CLKSRC_B)), cra);
	DEBIreplace(dev, k->MyCRB, CRBMSK_CLKENAB_A | CRBMSK_LATCHSRC, crb);
}