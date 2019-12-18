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
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  adap; } ;
struct tda18271_priv {unsigned char* tda18271_regs; TYPE_1__ i2c_props; int /*<<< orphan*/  id; int /*<<< orphan*/  lock; } ;
struct dvb_frontend {struct tda18271_priv* tuner_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t R_ID ; 
 int /*<<< orphan*/  TDA18271HDC1 ; 
 int /*<<< orphan*/  TDA18271HDC2 ; 
 int /*<<< orphan*/  i2c_adapter_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda18271_read_regs (struct dvb_frontend*) ; 
 int /*<<< orphan*/  tda_info (char*,...) ; 

__attribute__((used)) static int tda18271_get_id(struct dvb_frontend *fe)
{
	struct tda18271_priv *priv = fe->tuner_priv;
	unsigned char *regs = priv->tda18271_regs;
	char *name;

	mutex_lock(&priv->lock);
	tda18271_read_regs(fe);
	mutex_unlock(&priv->lock);

	switch (regs[R_ID] & 0x7f) {
	case 3:
		name = "TDA18271HD/C1";
		priv->id = TDA18271HDC1;
		break;
	case 4:
		name = "TDA18271HD/C2";
		priv->id = TDA18271HDC2;
		break;
	default:
		tda_info("Unknown device (%i) detected @ %d-%04x, device not supported.\n",
			 regs[R_ID], i2c_adapter_id(priv->i2c_props.adap),
			 priv->i2c_props.addr);
		return -EINVAL;
	}

	tda_info("%s detected @ %d-%04x\n", name,
		 i2c_adapter_id(priv->i2c_props.adap), priv->i2c_props.addr);

	return 0;
}