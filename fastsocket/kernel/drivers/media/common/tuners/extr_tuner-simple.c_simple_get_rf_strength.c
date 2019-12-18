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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * adap; } ;
struct tuner_simple_priv {TYPE_1__ i2c_props; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  tuner_dbg (char*,int) ; 
 int /*<<< orphan*/  tuner_read_status (struct dvb_frontend*) ; 
 int tuner_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simple_get_rf_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;
	int signal;

	if (priv->i2c_props.adap == NULL)
		return -EINVAL;

	signal = tuner_signal(tuner_read_status(fe));

	*strength = signal;

	tuner_dbg("Signal strength: %d\n", signal);

	return 0;
}