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
struct sd {int /*<<< orphan*/ * sensor; struct s5k83a_priv* sensor_priv; } ;
struct s5k83a_priv {struct s5k83a_priv* settings; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct s5k83a_priv*) ; 
 int /*<<< orphan*/  s5k83a_stop (struct sd*) ; 

void s5k83a_disconnect(struct sd *sd)
{
	struct s5k83a_priv *sens_priv = sd->sensor_priv;

	s5k83a_stop(sd);

	sd->sensor = NULL;
	kfree(sens_priv->settings);
	kfree(sens_priv);
}