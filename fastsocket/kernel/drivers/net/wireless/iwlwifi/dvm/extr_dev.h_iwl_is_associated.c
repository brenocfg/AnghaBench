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
struct iwl_priv {int /*<<< orphan*/ * contexts; } ;
typedef  enum iwl_rxon_context_id { ____Placeholder_iwl_rxon_context_id } iwl_rxon_context_id ;

/* Variables and functions */
 int iwl_is_associated_ctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int iwl_is_associated(struct iwl_priv *priv,
				    enum iwl_rxon_context_id ctxid)
{
	return iwl_is_associated_ctx(&priv->contexts[ctxid]);
}