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
typedef  int /*<<< orphan*/  u8 ;
struct atbm_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_AGC_HOLD_LOOP ; 
 int /*<<< orphan*/  REG_AGC_MAX ; 
 int /*<<< orphan*/  REG_AGC_MIN ; 
 int /*<<< orphan*/  atbm8830_write_reg (struct atbm_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_agc_config(struct atbm_state *priv,
	u8 min, u8 max, u8 hold_loop)
{
	/* no effect if both min and max are zero */
	if (!min && !max)
	    return 0;

	atbm8830_write_reg(priv, REG_AGC_MIN, min);
	atbm8830_write_reg(priv, REG_AGC_MAX, max);
	atbm8830_write_reg(priv, REG_AGC_HOLD_LOOP, hold_loop);

	return 0;
}