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
struct atbm_state {struct atbm8830_config* config; } ;
struct atbm8830_config {scalar_t__ ts_clk_gated; scalar_t__ ts_sampling_edge; scalar_t__ serial_ts; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TS_CLK_FREERUN ; 
 int /*<<< orphan*/  REG_TS_CLK_MODE ; 
 int /*<<< orphan*/  REG_TS_SAMPLE_EDGE ; 
 int /*<<< orphan*/  REG_TS_SERIAL ; 
 int /*<<< orphan*/  atbm8830_write_reg (struct atbm_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_ts_config(struct atbm_state *priv)
{
	const struct atbm8830_config *cfg = priv->config;

	/*Set parallel/serial ts mode*/
	atbm8830_write_reg(priv, REG_TS_SERIAL, cfg->serial_ts ? 1 : 0);
	atbm8830_write_reg(priv, REG_TS_CLK_MODE, cfg->serial_ts ? 1 : 0);
	/*Set ts sampling edge*/
	atbm8830_write_reg(priv, REG_TS_SAMPLE_EDGE,
		cfg->ts_sampling_edge ? 1 : 0);
	/*Set ts clock freerun*/
	atbm8830_write_reg(priv, REG_TS_CLK_FREERUN,
		cfg->ts_clk_gated ? 0 : 1);

	return 0;
}