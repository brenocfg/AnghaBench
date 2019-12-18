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

/* Variables and functions */
 int /*<<< orphan*/  EXAMPLE_I2S_CHANNEL_NUM ; 
 int /*<<< orphan*/  EXAMPLE_I2S_NUM ; 
 int /*<<< orphan*/  EXAMPLE_I2S_SAMPLE_BITS ; 
 int /*<<< orphan*/  EXAMPLE_I2S_SAMPLE_RATE ; 
 int /*<<< orphan*/  i2s_set_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void example_reset_play_mode(void)
{
    i2s_set_clk(EXAMPLE_I2S_NUM, EXAMPLE_I2S_SAMPLE_RATE, EXAMPLE_I2S_SAMPLE_BITS, EXAMPLE_I2S_CHANNEL_NUM);
}