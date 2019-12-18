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
typedef  int u8 ;
typedef  int u32 ;
struct tunertype {int stepsize; int /*<<< orphan*/  name; } ;
struct tuner_simple_priv {struct tunertype* tun; int /*<<< orphan*/  type; } ;
struct tuner_params {unsigned int iffreq; } ;
struct dvb_frontend_parameters {int frequency; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_PARAM_TYPE_DIGITAL ; 
 unsigned int offset ; 
 int simple_config_lookup (struct dvb_frontend*,struct tuner_params*,unsigned int*,int*,int*) ; 
 int /*<<< orphan*/  simple_set_dvb (struct dvb_frontend*,int*,struct dvb_frontend_parameters const*) ; 
 struct tuner_params* simple_tuner_params (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  tuner_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 simple_dvb_configure(struct dvb_frontend *fe, u8 *buf,
				const struct dvb_frontend_parameters *params)
{
	/* This function returns the tuned frequency on success, 0 on error */
	struct tuner_simple_priv *priv = fe->tuner_priv;
	struct tunertype *tun = priv->tun;
	static struct tuner_params *t_params;
	u8 config, cb;
	u32 div;
	int ret;
	unsigned frequency = params->frequency / 62500;

	if (!tun->stepsize) {
		/* tuner-core was loaded before the digital tuner was
		 * configured and somehow picked the wrong tuner type */
		tuner_err("attempt to treat tuner %d (%s) as digital tuner "
			  "without stepsize defined.\n",
			  priv->type, priv->tun->name);
		return 0; /* failure */
	}

	t_params = simple_tuner_params(fe, TUNER_PARAM_TYPE_DIGITAL);
	ret = simple_config_lookup(fe, t_params, &frequency, &config, &cb);
	if (ret < 0)
		return 0; /* failure */

	div = ((frequency + t_params->iffreq) * 62500 + offset +
	       tun->stepsize/2) / tun->stepsize;

	buf[0] = div >> 8;
	buf[1] = div & 0xff;
	buf[2] = config;
	buf[3] = cb;

	simple_set_dvb(fe, buf, params);

	tuner_dbg("%s: div=%d | buf=0x%02x,0x%02x,0x%02x,0x%02x\n",
		  tun->name, div, buf[0], buf[1], buf[2], buf[3]);

	/* calculate the frequency we set it to */
	return (div * tun->stepsize) - t_params->iffreq;
}