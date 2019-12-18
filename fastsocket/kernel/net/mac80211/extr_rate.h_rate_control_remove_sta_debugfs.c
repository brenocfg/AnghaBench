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
struct sta_info {int /*<<< orphan*/  rate_ctrl_priv; struct rate_control_ref* rate_ctrl; } ;
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove_sta_debugfs ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rate_control_remove_sta_debugfs(struct sta_info *sta)
{
#ifdef CONFIG_MAC80211_DEBUGFS
	struct rate_control_ref *ref = sta->rate_ctrl;
	if (ref && ref->ops->remove_sta_debugfs)
		ref->ops->remove_sta_debugfs(ref->priv, sta->rate_ctrl_priv);
#endif
}