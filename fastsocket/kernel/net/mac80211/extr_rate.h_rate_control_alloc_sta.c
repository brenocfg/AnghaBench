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
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {void* (* alloc_sta ) (int /*<<< orphan*/ ,struct ieee80211_sta*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 void* stub1 (int /*<<< orphan*/ ,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *rate_control_alloc_sta(struct rate_control_ref *ref,
					   struct ieee80211_sta *sta,
					   gfp_t gfp)
{
	return ref->ops->alloc_sta(ref->priv, sta, gfp);
}