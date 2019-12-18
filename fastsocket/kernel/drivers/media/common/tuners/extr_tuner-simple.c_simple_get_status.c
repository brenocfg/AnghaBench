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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * adap; } ;
struct tuner_simple_priv {int /*<<< orphan*/  type; TYPE_1__ i2c_props; } ;
struct dvb_frontend {struct tuner_simple_priv* tuner_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TUNER_STATUS_LOCKED ; 
 int /*<<< orphan*/  TUNER_STATUS_STEREO ; 
 int /*<<< orphan*/  tuner_afcstatus (int) ; 
 int /*<<< orphan*/  tuner_dbg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tuner_islocked (int) ; 
 int tuner_read_status (struct dvb_frontend*) ; 
 scalar_t__ tuner_stereo (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int simple_get_status(struct dvb_frontend *fe, u32 *status)
{
	struct tuner_simple_priv *priv = fe->tuner_priv;
	int tuner_status;

	if (priv->i2c_props.adap == NULL)
		return -EINVAL;

	tuner_status = tuner_read_status(fe);

	*status = 0;

	if (tuner_islocked(tuner_status))
		*status = TUNER_STATUS_LOCKED;
	if (tuner_stereo(priv->type, tuner_status))
		*status |= TUNER_STATUS_STEREO;

	tuner_dbg("AFC Status: %d\n", tuner_afcstatus(tuner_status));

	return 0;
}