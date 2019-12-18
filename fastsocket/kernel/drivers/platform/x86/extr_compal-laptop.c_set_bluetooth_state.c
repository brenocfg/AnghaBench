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
typedef  int u8 ;

/* Variables and functions */
 int BT_MASK ; 
 int /*<<< orphan*/  COMPAL_EC_COMMAND_WIRELESS ; 
 int EINVAL ; 
 int KILLSWITCH_MASK ; 
 int /*<<< orphan*/  ec_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_bluetooth_state(int state)
{
	u8 result, value;

	ec_read(COMPAL_EC_COMMAND_WIRELESS, &result);

	if ((result & KILLSWITCH_MASK) == 0)
		return -EINVAL;
	else {
		if (state)
			value = (u8) (result | BT_MASK);
		else
			value = (u8) (result & ~BT_MASK);
		ec_write(COMPAL_EC_COMMAND_WIRELESS, value);
	}

	return 0;
}