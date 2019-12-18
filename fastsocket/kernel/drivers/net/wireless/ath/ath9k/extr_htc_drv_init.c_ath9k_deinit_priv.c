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
struct ath9k_htc_priv {int /*<<< orphan*/ * ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_deinit_priv(struct ath9k_htc_priv *priv)
{
	ath9k_hw_deinit(priv->ah);
	kfree(priv->ah);
	priv->ah = NULL;
}