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
 int EIO ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 scalar_t__ ZCD_ALLOW_MS ; 
 scalar_t__ ZCD_FORCE_MODEM ; 
 int option_inquiry (struct us_data*) ; 
 int option_rezero (struct us_data*) ; 
 scalar_t__ option_zero_cd ; 

int option_ms_init(struct us_data *us)
{
	int result;

	US_DEBUGP("Option MS: option_ms_init called\n");

	/* Additional test for vendor information via INQUIRY,
	 * because some vendor/product IDs are ambiguous
	 */
	result = option_inquiry(us);
	if (result != 0) {
		US_DEBUGP("Option MS: vendor is not Option or not determinable,"
			  " no action taken\n");
		return 0;
	} else
		US_DEBUGP("Option MS: this is a genuine Option device,"
			  " proceeding\n");

	/* Force Modem mode */
	if (option_zero_cd == ZCD_FORCE_MODEM) {
		US_DEBUGP("Option MS: %s", "Forcing Modem Mode\n");
		result = option_rezero(us);
		if (result != USB_STOR_XFER_GOOD)
			US_DEBUGP("Option MS: Failed to switch to modem mode.\n");
		return -EIO;
	} else if (option_zero_cd == ZCD_ALLOW_MS) {
		/* Allow Mass Storage mode (keep CD-Rom) */
		US_DEBUGP("Option MS: %s", "Allowing Mass Storage Mode if device"
		          " requests it\n");
	}

	return 0;
}