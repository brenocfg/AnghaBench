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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 

__attribute__((used)) static u16 b43legacy_get_txgain_base_band(u16 txpower)
{
	u16 ret;

	B43legacy_WARN_ON(txpower > 63);

	if (txpower >= 54)
		ret = 2;
	else if (txpower >= 49)
		ret = 4;
	else if (txpower >= 44)
		ret = 5;
	else
		ret = 6;

	return ret;
}