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
typedef  size_t u_int ;
struct ahc_syncrate {int sxfr_u2; size_t period; int /*<<< orphan*/ * rate; } ;
struct ahc_softc {int features; } ;

/* Variables and functions */
 int AHC_DT ; 
 size_t AHC_SYNCRATE_FAST ; 
 size_t AHC_SYNCRATE_ULTRA ; 
 size_t AHC_SYNCRATE_ULTRA2 ; 
 int AHC_ULTRA ; 
 int AHC_ULTRA2 ; 
 size_t MSG_EXT_PPR_DT_REQ ; 
 int ST_SXFR ; 
 struct ahc_syncrate const* ahc_syncrates ; 

const struct ahc_syncrate *
ahc_find_syncrate(struct ahc_softc *ahc, u_int *period,
		  u_int *ppr_options, u_int maxsync)
{
	const struct ahc_syncrate *syncrate;

	if ((ahc->features & AHC_DT) == 0)
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;

	/* Skip all DT only entries if DT is not available */
	if ((*ppr_options & MSG_EXT_PPR_DT_REQ) == 0
	 && maxsync < AHC_SYNCRATE_ULTRA2)
		maxsync = AHC_SYNCRATE_ULTRA2;

	/* Now set the maxsync based on the card capabilities
	 * DT is already done above */
	if ((ahc->features & (AHC_DT | AHC_ULTRA2)) == 0
	    && maxsync < AHC_SYNCRATE_ULTRA)
		maxsync = AHC_SYNCRATE_ULTRA;
	if ((ahc->features & (AHC_DT | AHC_ULTRA2 | AHC_ULTRA)) == 0
	    && maxsync < AHC_SYNCRATE_FAST)
		maxsync = AHC_SYNCRATE_FAST;

	for (syncrate = &ahc_syncrates[maxsync];
	     syncrate->rate != NULL;
	     syncrate++) {

		/*
		 * The Ultra2 table doesn't go as low
		 * as for the Fast/Ultra cards.
		 */
		if ((ahc->features & AHC_ULTRA2) != 0
		 && (syncrate->sxfr_u2 == 0))
			break;

		if (*period <= syncrate->period) {
			/*
			 * When responding to a target that requests
			 * sync, the requested rate may fall between
			 * two rates that we can output, but still be
			 * a rate that we can receive.  Because of this,
			 * we want to respond to the target with
			 * the same rate that it sent to us even
			 * if the period we use to send data to it
			 * is lower.  Only lower the response period
			 * if we must.
			 */
			if (syncrate == &ahc_syncrates[maxsync])
				*period = syncrate->period;

			/*
			 * At some speeds, we only support
			 * ST transfers.
			 */
		 	if ((syncrate->sxfr_u2 & ST_SXFR) != 0)
				*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
			break;
		}
	}

	if ((*period == 0)
	 || (syncrate->rate == NULL)
	 || ((ahc->features & AHC_ULTRA2) != 0
	  && (syncrate->sxfr_u2 == 0))) {
		/* Use asynchronous transfers. */
		*period = 0;
		syncrate = NULL;
		*ppr_options &= ~MSG_EXT_PPR_DT_REQ;
	}
	return (syncrate);
}