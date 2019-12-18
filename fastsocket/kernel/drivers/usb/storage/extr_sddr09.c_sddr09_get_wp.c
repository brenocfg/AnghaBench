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
struct sddr09_card_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned char LUNBITS ; 
 int /*<<< orphan*/  SDDR09_WP ; 
 int /*<<< orphan*/  US_DEBUGP (char*,...) ; 
 int sddr09_read_status (struct us_data*,unsigned char*) ; 

__attribute__((used)) static int
sddr09_get_wp(struct us_data *us, struct sddr09_card_info *info) {
	int result;
	unsigned char status;

	result = sddr09_read_status(us, &status);
	if (result) {
		US_DEBUGP("sddr09_get_wp: read_status fails\n");
		return result;
	}
	US_DEBUGP("sddr09_get_wp: status 0x%02X", status);
	if ((status & 0x80) == 0) {
		info->flags |= SDDR09_WP;	/* write protected */
		US_DEBUGP(" WP");
	}
	if (status & 0x40)
		US_DEBUGP(" Ready");
	if (status & LUNBITS)
		US_DEBUGP(" Suspended");
	if (status & 0x1)
		US_DEBUGP(" Error");
	US_DEBUGP("\n");
	return 0;
}