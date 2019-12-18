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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int EINVAL ; 
 scalar_t__ LSB (int /*<<< orphan*/ ) ; 
 scalar_t__ MSB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCDB (struct qlcnic_adapter*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ __QLCNIC_MAX_LED_RATE ; 
 scalar_t__ __QLCNIC_MAX_LED_STATE ; 

__attribute__((used)) static int qlcnic_validate_beacon(struct qlcnic_adapter *adapter, u16 beacon,
				  u8 *state, u8 *rate)
{
	*rate = LSB(beacon);
	*state = MSB(beacon);

	QLCDB(adapter, DRV, "rate %x state %x\n", *rate, *state);

	if (!*state) {
		*rate = __QLCNIC_MAX_LED_RATE;
		return 0;
	} else if (*state > __QLCNIC_MAX_LED_STATE) {
		return -EINVAL;
	}

	if ((!*rate) || (*rate > __QLCNIC_MAX_LED_RATE))
		return -EINVAL;

	return 0;
}