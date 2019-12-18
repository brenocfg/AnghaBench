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
struct TYPE_6__ {TYPE_2__* adap; } ;
struct xc2028_data {TYPE_3__ i2c_props; } ;
struct dvb_frontend {int (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ;TYPE_1__* dvb; struct xc2028_data* tuner_priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  algo_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVB_FRONTEND_COMPONENT_TUNER ; 
 int EINVAL ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int do_tuner_callback(struct dvb_frontend *fe, int cmd, int arg)
{
	struct xc2028_data *priv = fe->tuner_priv;

	/* analog side (tuner-core) uses i2c_adap->algo_data.
	 * digital side is not guaranteed to have algo_data defined.
	 *
	 * digital side will always have fe->dvb defined.
	 * analog side (tuner-core) doesn't (yet) define fe->dvb.
	 */

	return (!fe->callback) ? -EINVAL :
		fe->callback(((fe->dvb) && (fe->dvb->priv)) ?
				fe->dvb->priv : priv->i2c_props.adap->algo_data,
			     DVB_FRONTEND_COMPONENT_TUNER, cmd, arg);
}