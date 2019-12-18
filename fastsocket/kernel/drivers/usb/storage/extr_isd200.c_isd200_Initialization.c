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
 scalar_t__ ISD200_ERROR ; 
 scalar_t__ ISD200_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*) ; 
 scalar_t__ isd200_get_inquiry_data (struct us_data*) ; 
 scalar_t__ isd200_init_info (struct us_data*) ; 

__attribute__((used)) static int isd200_Initialization(struct us_data *us)
{
	US_DEBUGP("ISD200 Initialization...\n");

	/* Initialize ISD200 info struct */

	if (isd200_init_info(us) == ISD200_ERROR) {
		US_DEBUGP("ERROR Initializing ISD200 Info struct\n");
	} else {
		/* Get device specific data */

		if (isd200_get_inquiry_data(us) != ISD200_GOOD)
			US_DEBUGP("ISD200 Initialization Failure\n");
		else
			US_DEBUGP("ISD200 Initialization complete\n");
	}

	return 0;
}