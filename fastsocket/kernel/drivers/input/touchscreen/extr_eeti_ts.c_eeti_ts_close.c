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
struct input_dev {int dummy; } ;
struct eeti_ts_priv {int /*<<< orphan*/  work; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct eeti_ts_priv* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void eeti_ts_close(struct input_dev *dev)
{
	struct eeti_ts_priv *priv = input_get_drvdata(dev);

	disable_irq(priv->irq);
	cancel_work_sync(&priv->work);
}