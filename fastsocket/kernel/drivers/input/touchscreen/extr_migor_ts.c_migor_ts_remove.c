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
struct migor_ts_priv {int /*<<< orphan*/  input; int /*<<< orphan*/  irq; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct migor_ts_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct migor_ts_priv*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct migor_ts_priv*) ; 

__attribute__((used)) static int migor_ts_remove(struct i2c_client *client)
{
	struct migor_ts_priv *priv = dev_get_drvdata(&client->dev);

	free_irq(priv->irq, priv);
	input_unregister_device(priv->input);
	kfree(priv);

	dev_set_drvdata(&client->dev, NULL);

	return 0;
}