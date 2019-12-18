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
struct ath9k_htc_priv {int /*<<< orphan*/  op_flags; int /*<<< orphan*/  ani_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ANI_RUNNING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath9k_htc_stop_ani(struct ath9k_htc_priv *priv)
{
	cancel_delayed_work_sync(&priv->ani_work);
	clear_bit(OP_ANI_RUNNING, &priv->op_flags);
}