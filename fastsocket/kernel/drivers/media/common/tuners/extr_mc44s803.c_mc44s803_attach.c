#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct mc44s803_priv {struct dvb_frontend* fe; struct i2c_adapter* i2c; struct mc44s803_config* cfg; } ;
struct mc44s803_config {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct mc44s803_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  MC44S803_ID ; 
 int /*<<< orphan*/  MC44S803_REG_ID ; 
 int MC44S803_REG_MS (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mc44s803_priv*) ; 
 struct mc44s803_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mc44s803_readreg (struct mc44s803_priv*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mc44s803_tuner_ops ; 
 int /*<<< orphan*/  mc_printk (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub3 (struct dvb_frontend*,int) ; 

struct dvb_frontend *mc44s803_attach(struct dvb_frontend *fe,
	 struct i2c_adapter *i2c, struct mc44s803_config *cfg)
{
	struct mc44s803_priv *priv;
	u32 reg;
	u8 id;
	int ret;

	reg = 0;

	priv = kzalloc(sizeof(struct mc44s803_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	priv->cfg = cfg;
	priv->i2c = i2c;
	priv->fe  = fe;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1); /* open i2c_gate */

	ret = mc44s803_readreg(priv, MC44S803_REG_ID, &reg);
	if (ret)
		goto error;

	id = MC44S803_REG_MS(reg, MC44S803_ID);

	if (id != 0x14) {
		mc_printk(KERN_ERR, "unsupported ID "
		       "(%x should be 0x14)\n", id);
		goto error;
	}

	mc_printk(KERN_INFO, "successfully identified (ID = %x)\n", id);
	memcpy(&fe->ops.tuner_ops, &mc44s803_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	fe->tuner_priv = priv;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	return fe;

error:
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0); /* close i2c_gate */

	kfree(priv);
	return NULL;
}