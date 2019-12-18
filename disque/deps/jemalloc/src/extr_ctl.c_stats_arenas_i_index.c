#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl_named_node_t ;
struct TYPE_4__ {size_t narenas; TYPE_1__* arenas; } ;
struct TYPE_3__ {int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctl_mtx ; 
 TYPE_2__ ctl_stats ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * super_stats_arenas_i_node ; 

__attribute__((used)) static const ctl_named_node_t *
stats_arenas_i_index(const size_t *mib, size_t miblen, size_t i)
{
	const ctl_named_node_t * ret;

	malloc_mutex_lock(&ctl_mtx);
	if (i > ctl_stats.narenas || !ctl_stats.arenas[i].initialized) {
		ret = NULL;
		goto label_return;
	}

	ret = super_stats_arenas_i_node;
label_return:
	malloc_mutex_unlock(&ctl_mtx);
	return (ret);
}