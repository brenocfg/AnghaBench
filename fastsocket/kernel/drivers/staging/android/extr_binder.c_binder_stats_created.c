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
typedef  enum binder_stat_types { ____Placeholder_binder_stat_types } binder_stat_types ;
struct TYPE_2__ {int /*<<< orphan*/ * obj_created; } ;

/* Variables and functions */
 TYPE_1__ binder_stats ; 

__attribute__((used)) static inline void binder_stats_created(enum binder_stat_types type)
{
	binder_stats.obj_created[type]++;
}