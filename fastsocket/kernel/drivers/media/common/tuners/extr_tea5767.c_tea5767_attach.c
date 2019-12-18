#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int port1; int port2; int high_cut; int st_noise; int japan_band; int /*<<< orphan*/  xtal_freq; } ;
struct TYPE_4__ {char* name; struct i2c_adapter* adap; int /*<<< orphan*/  addr; } ;
struct tea5767_priv {TYPE_2__ ctrl; TYPE_1__ i2c_props; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_3__ ops; struct tea5767_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TEA5767_HIGH_LO_32768 ; 
 struct tea5767_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tea5767_tuner_ops ; 
 int /*<<< orphan*/  tuner_info (char*,char*) ; 

struct dvb_frontend *tea5767_attach(struct dvb_frontend *fe,
				    struct i2c_adapter* i2c_adap,
				    u8 i2c_addr)
{
	struct tea5767_priv *priv = NULL;

	priv = kzalloc(sizeof(struct tea5767_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;
	fe->tuner_priv = priv;

	priv->i2c_props.addr  = i2c_addr;
	priv->i2c_props.adap  = i2c_adap;
	priv->i2c_props.name  = "tea5767";

	priv->ctrl.xtal_freq  = TEA5767_HIGH_LO_32768;
	priv->ctrl.port1      = 1;
	priv->ctrl.port2      = 1;
	priv->ctrl.high_cut   = 1;
	priv->ctrl.st_noise   = 1;
	priv->ctrl.japan_band = 1;

	memcpy(&fe->ops.tuner_ops, &tea5767_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	tuner_info("type set to %s\n", "Philips TEA5767HN FM Radio");

	return fe;
}