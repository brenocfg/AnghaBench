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
typedef  int /*<<< orphan*/  u32 ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_RV_BITS ; 
 int /*<<< orphan*/  UW2453_REGWRITE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uw2453_autocal_synth ; 
 int /*<<< orphan*/ * uw2453_std_synth ; 
 int /*<<< orphan*/ * uw2453_synth_divide ; 
 int zd_rfwrite_locked (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uw2453_synth_set_channel(struct zd_chip *chip, int channel,
	bool autocal)
{
	int r;
	int idx = channel - 1;
	u32 val;

	if (autocal)
		val = UW2453_REGWRITE(1, uw2453_autocal_synth[idx]);
	else
		val = UW2453_REGWRITE(1, uw2453_std_synth[idx]);

	r = zd_rfwrite_locked(chip, val, RF_RV_BITS);
	if (r)
		return r;

	return zd_rfwrite_locked(chip,
		UW2453_REGWRITE(2, uw2453_synth_divide[idx]), RF_RV_BITS);
}