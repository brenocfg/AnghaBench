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
struct sd {struct s5k83a_priv* sensor_priv; } ;
struct s5k83a_priv {scalar_t__ rotation_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int s5k83a_set_led_indication (struct sd*,int /*<<< orphan*/ ) ; 

int s5k83a_stop(struct sd *sd)
{
	struct s5k83a_priv *sens_priv = sd->sensor_priv;

	if (sens_priv->rotation_thread)
		kthread_stop(sens_priv->rotation_thread);

	return s5k83a_set_led_indication(sd, 0);
}