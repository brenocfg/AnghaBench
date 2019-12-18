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
struct iwl_rxon_context {int dummy; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int iwl_send_static_wepkey_cmd (struct iwl_priv*,struct iwl_rxon_context*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_restore_default_wep_keys(struct iwl_priv *priv,
				 struct iwl_rxon_context *ctx)
{
	lockdep_assert_held(&priv->mutex);

	return iwl_send_static_wepkey_cmd(priv, ctx, false);
}