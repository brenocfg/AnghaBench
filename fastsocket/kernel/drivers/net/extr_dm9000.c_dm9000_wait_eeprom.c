#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_EPCR ; 
 unsigned int EPCR_ERRE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned int dm9000_read_locked (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dm9000_wait_eeprom(board_info_t *db)
{
	unsigned int status;
	int timeout = 8;	/* wait max 8msec */

	/* The DM9000 data sheets say we should be able to
	 * poll the ERRE bit in EPCR to wait for the EEPROM
	 * operation. From testing several chips, this bit
	 * does not seem to work.
	 *
	 * We attempt to use the bit, but fall back to the
	 * timeout (which is why we do not return an error
	 * on expiry) to say that the EEPROM operation has
	 * completed.
	 */

	while (1) {
		status = dm9000_read_locked(db, DM9000_EPCR);

		if ((status & EPCR_ERRE) == 0)
			break;

		msleep(1);

		if (timeout-- < 0) {
			dev_dbg(db->dev, "timeout waiting EEPROM\n");
			break;
		}
	}

	return 0;
}