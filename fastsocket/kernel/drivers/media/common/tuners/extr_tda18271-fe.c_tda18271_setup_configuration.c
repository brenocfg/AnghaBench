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
struct tda18271_priv {int /*<<< orphan*/  output_opt; int /*<<< orphan*/  small_i2c; int /*<<< orphan*/  config; int /*<<< orphan*/  role; int /*<<< orphan*/  gate; } ;
struct tda18271_config {int /*<<< orphan*/  output_opt; int /*<<< orphan*/  small_i2c; int /*<<< orphan*/  config; int /*<<< orphan*/  role; int /*<<< orphan*/  gate; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDA18271_39_BYTE_CHUNK_INIT ; 
 int /*<<< orphan*/  TDA18271_GATE_AUTO ; 
 int /*<<< orphan*/  TDA18271_MASTER ; 
 int /*<<< orphan*/  TDA18271_OUTPUT_LT_XT_ON ; 

__attribute__((used)) static int tda18271_setup_configuration(struct dvb_frontend *fe,
					struct tda18271_config *cfg)
{
	struct tda18271_priv *priv = fe->tuner_priv;

	priv->gate = (cfg) ? cfg->gate : TDA18271_GATE_AUTO;
	priv->role = (cfg) ? cfg->role : TDA18271_MASTER;
	priv->config = (cfg) ? cfg->config : 0;
	priv->small_i2c = (cfg) ?
		cfg->small_i2c : TDA18271_39_BYTE_CHUNK_INIT;
	priv->output_opt = (cfg) ?
		cfg->output_opt : TDA18271_OUTPUT_LT_XT_ON;

	return 0;
}