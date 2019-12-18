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
typedef  int /*<<< orphan*/  vpd ;
typedef  int u8 ;
struct prpmc2800_board_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM2_ADDR ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mv64x60_i2c_close () ; 
 scalar_t__ mv64x60_i2c_open () ; 
 int mv64x60_i2c_read (int /*<<< orphan*/ ,int*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 struct prpmc2800_board_info* prpmc2800_get_board_info (int*) ; 

__attribute__((used)) static struct prpmc2800_board_info *prpmc2800_get_bip(void)
{
	struct prpmc2800_board_info *bip;
	u8 vpd[5];
	int rc;

	if (mv64x60_i2c_open())
		fatal("Error: Can't open i2c device\n\r");

	/* Get VPD from i2c eeprom-2 */
	memset(vpd, 0, sizeof(vpd));
	rc = mv64x60_i2c_read(EEPROM2_ADDR, vpd, 0x1fde, 2, sizeof(vpd));
	if (rc < 0)
		fatal("Error: Couldn't read eeprom2\n\r");
	mv64x60_i2c_close();

	/* Get board type & related info */
	bip = prpmc2800_get_board_info(vpd);
	if (bip == NULL) {
		printf("Error: Unsupported board or corrupted VPD:\n\r");
		printf("  0x%x 0x%x 0x%x 0x%x 0x%x\n\r",
				vpd[0], vpd[1], vpd[2], vpd[3], vpd[4]);
		printf("Using device tree defaults...\n\r");
	}

	return bip;
}