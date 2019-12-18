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
struct migor_ts_priv {int /*<<< orphan*/  irq; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 struct migor_ts_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq_wake (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int migor_ts_suspend(struct i2c_client *client, pm_message_t mesg)
{
	struct migor_ts_priv *priv = dev_get_drvdata(&client->dev);

	if (device_may_wakeup(&client->dev))
		enable_irq_wake(priv->irq);

	return 0;
}