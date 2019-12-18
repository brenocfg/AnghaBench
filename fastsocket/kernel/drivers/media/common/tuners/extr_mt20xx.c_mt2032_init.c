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
struct microtune_priv {int xogc; int /*<<< orphan*/  i2c_props; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; struct microtune_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mt2032_tuner_ops ; 
 int /*<<< orphan*/  tuner_dbg (char*,int) ; 
 int /*<<< orphan*/  tuner_i2c_xfer_recv (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int tuner_i2c_xfer_send (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  tuner_warn (char*,int) ; 

__attribute__((used)) static int mt2032_init(struct dvb_frontend *fe)
{
	struct microtune_priv *priv = fe->tuner_priv;
	unsigned char buf[21];
	int ret,xogc,xok=0;

	// Initialize Registers per spec.
	buf[1]=2; // Index to register 2
	buf[2]=0xff;
	buf[3]=0x0f;
	buf[4]=0x1f;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+1,4);

	buf[5]=6; // Index register 6
	buf[6]=0xe4;
	buf[7]=0x8f;
	buf[8]=0xc3;
	buf[9]=0x4e;
	buf[10]=0xec;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+5,6);

	buf[12]=13;  // Index register 13
	buf[13]=0x32;
	ret=tuner_i2c_xfer_send(&priv->i2c_props,buf+12,2);

	// Adjust XOGC (register 7), wait for XOK
	xogc=7;
	do {
		tuner_dbg("mt2032: xogc = 0x%02x\n",xogc&0x07);
		mdelay(10);
		buf[0]=0x0e;
		tuner_i2c_xfer_send(&priv->i2c_props,buf,1);
		tuner_i2c_xfer_recv(&priv->i2c_props,buf,1);
		xok=buf[0]&0x01;
		tuner_dbg("mt2032: xok = 0x%02x\n",xok);
		if (xok == 1) break;

		xogc--;
		tuner_dbg("mt2032: xogc = 0x%02x\n",xogc&0x07);
		if (xogc == 3) {
			xogc=4; // min. 4 per spec
			break;
		}
		buf[0]=0x07;
		buf[1]=0x88 + xogc;
		ret=tuner_i2c_xfer_send(&priv->i2c_props,buf,2);
		if (ret!=2)
			tuner_warn("i2c i/o error: rc == %d (should be 2)\n",ret);
	} while (xok != 1 );
	priv->xogc=xogc;

	memcpy(&fe->ops.tuner_ops, &mt2032_tuner_ops, sizeof(struct dvb_tuner_ops));

	return(1);
}