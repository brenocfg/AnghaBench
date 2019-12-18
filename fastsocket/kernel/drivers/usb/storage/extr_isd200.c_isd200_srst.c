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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_REENABLE ; 
 int /*<<< orphan*/  ACTION_RESET ; 
 int ISD200_ERROR ; 
 int ISD200_GOOD ; 
 int ISD200_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int isd200_action (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int isd200_srst( struct us_data *us ) 
{
	int retStatus = ISD200_GOOD;
	int transferStatus;

	US_DEBUGP("Entering isd200_SRST\n");

	transferStatus = isd200_action( us, ACTION_RESET, NULL, 0 );

	/* check to see if this request failed */
	if (transferStatus != ISD200_TRANSPORT_GOOD) {
		US_DEBUGP("   Error issuing SRST\n");
		retStatus = ISD200_ERROR;
	} else {
		/* delay 10ms to give the drive a chance to see it */
		msleep(10);

		transferStatus = isd200_action( us, ACTION_REENABLE, NULL, 0 );
		if (transferStatus != ISD200_TRANSPORT_GOOD) {
			US_DEBUGP("   Error taking drive out of reset\n");
			retStatus = ISD200_ERROR;
		} else {
			/* delay 50ms to give the drive a chance to recover after SRST */
			msleep(50);
		}
	}

	US_DEBUGP("Leaving isd200_srst %08X\n", retStatus);
	return retStatus;
}