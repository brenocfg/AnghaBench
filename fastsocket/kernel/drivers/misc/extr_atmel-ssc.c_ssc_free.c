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
struct ssc_device {TYPE_1__* pdev; int /*<<< orphan*/  clk; scalar_t__ user; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_lock ; 

void ssc_free(struct ssc_device *ssc)
{
	spin_lock(&user_lock);
	if (ssc->user) {
		ssc->user--;
		clk_disable(ssc->clk);
	} else {
		dev_dbg(&ssc->pdev->dev, "device already free\n");
	}
	spin_unlock(&user_lock);
}