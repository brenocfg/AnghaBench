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
struct microtune_priv {int /*<<< orphan*/  i2c_props; } ;
struct dvb_frontend {struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tuner_dbg (char*,unsigned char) ; 
 int tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void mt2050_set_antenna(struct dvb_frontend *fe, unsigned char antenna)
{
	struct microtune_priv *priv = fe->tuner_priv;
	unsigned char buf[2];
	int ret;

	buf[0] = 6;
	buf[1] = antenna ? 0x11 : 0x10;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
	tuner_dbg("mt2050: enabled antenna connector %d\n", antenna);
}