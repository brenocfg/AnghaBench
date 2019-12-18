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
struct tea5767_priv {int /*<<< orphan*/  ctrl; } ;
struct dvb_frontend {struct tea5767_priv* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int tea5767_set_config (struct dvb_frontend *fe, void *priv_cfg)
{
	struct tea5767_priv *priv = fe->tuner_priv;

	memcpy(&priv->ctrl, priv_cfg, sizeof(priv->ctrl));

	return 0;
}