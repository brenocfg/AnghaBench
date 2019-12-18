#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  holding_time; } ;
struct TYPE_5__ {TYPE_1__ ctrl_info; int /*<<< orphan*/  entry_state; int /*<<< orphan*/  tv; } ;
typedef  TYPE_2__ eg_cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  EGRESS_RESOLVED ; 
 int /*<<< orphan*/  do_gettimeofday (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_eg_cache_entry(eg_cache_entry * entry, uint16_t holding_time)
{
	do_gettimeofday(&(entry->tv));
	entry->entry_state = EGRESS_RESOLVED;
	entry->ctrl_info.holding_time = holding_time;

	return;
}