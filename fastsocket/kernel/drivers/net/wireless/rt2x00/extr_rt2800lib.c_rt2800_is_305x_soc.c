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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF3020 ; 
 int /*<<< orphan*/  RF3021 ; 
 int /*<<< orphan*/  RF3022 ; 
 int /*<<< orphan*/  RT2872 ; 
 int /*<<< orphan*/  rt2x00_is_soc (struct rt2x00_dev*) ; 
 scalar_t__ rt2x00_rf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_warn (struct rt2x00_dev*,char*) ; 

__attribute__((used)) static inline bool rt2800_is_305x_soc(struct rt2x00_dev *rt2x00dev)
{
	/* check for rt2872 on SoC */
	if (!rt2x00_is_soc(rt2x00dev) ||
	    !rt2x00_rt(rt2x00dev, RT2872))
		return false;

	/* we know for sure that these rf chipsets are used on rt305x boards */
	if (rt2x00_rf(rt2x00dev, RF3020) ||
	    rt2x00_rf(rt2x00dev, RF3021) ||
	    rt2x00_rf(rt2x00dev, RF3022))
		return true;

	rt2x00_warn(rt2x00dev, "Unknown RF chipset on rt305x\n");
	return false;
}