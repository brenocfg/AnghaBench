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
struct tid_ampdu_tx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * tid_tx; } ;
struct sta_info {TYPE_1__ ampdu_mlme; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct tid_ampdu_tx* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline struct tid_ampdu_tx *
rcu_dereference_protected_tid_tx(struct sta_info *sta, int tid)
{
	return rcu_dereference_protected(sta->ampdu_mlme.tid_tx[tid],
					 lockdep_is_held(&sta->lock) ||
					 lockdep_is_held(&sta->ampdu_mlme.mtx));
}