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
typedef  int /*<<< orphan*/  u8 ;
struct si4713_device {scalar_t__ power_state; TYPE_1__* platform_data; int /*<<< orphan*/  sd; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_power ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 scalar_t__ POWER_OFF ; 
 int /*<<< orphan*/  SI4713_CMD_POWER_DOWN ; 
 int SI4713_PWDN_NRESP ; 
 int /*<<< orphan*/  debug ; 
 int si4713_send_command (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int si4713_powerdown(struct si4713_device *sdev)
{
	int err;
	u8 resp[SI4713_PWDN_NRESP];

	if (!sdev->power_state)
		return 0;

	err = si4713_send_command(sdev, SI4713_CMD_POWER_DOWN,
					NULL, 0,
					resp, ARRAY_SIZE(resp),
					DEFAULT_TIMEOUT);

	if (!err) {
		v4l2_dbg(1, debug, &sdev->sd, "Power down response: 0x%02x\n",
				resp[0]);
		v4l2_dbg(1, debug, &sdev->sd, "Device in reset mode\n");
		sdev->platform_data->set_power(0);
		sdev->power_state = POWER_OFF;
	}

	return err;
}