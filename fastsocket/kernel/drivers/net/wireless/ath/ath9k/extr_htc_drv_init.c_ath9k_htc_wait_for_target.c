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
struct ath9k_htc_priv {TYPE_1__* htc; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgt_ready; int /*<<< orphan*/  target_wait; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath9k_htc_wait_for_target(struct ath9k_htc_priv *priv)
{
	int time_left;

	if (atomic_read(&priv->htc->tgt_ready) > 0) {
		atomic_dec(&priv->htc->tgt_ready);
		return 0;
	}

	/* Firmware can take up to 50ms to get ready, to be safe use 1 second */
	time_left = wait_for_completion_timeout(&priv->htc->target_wait, HZ);
	if (!time_left) {
		dev_err(priv->dev, "ath9k_htc: Target is unresponsive\n");
		return -ETIMEDOUT;
	}

	atomic_dec(&priv->htc->tgt_ready);

	return 0;
}