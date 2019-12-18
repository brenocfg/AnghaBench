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
typedef  int /*<<< orphan*/  bondport_ref ;
struct TYPE_2__ {scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  bondport_flags_clear_mux_attached (int /*<<< orphan*/ ) ; 
 scalar_t__ bondport_flags_mux_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bondport_get_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* g_bond ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bondport_DetachMuxFromAggregator(bondport_ref p)
{
    if (bondport_flags_mux_attached(p)) {
	if (g_bond->verbose) {
	    timestamp_printf("[%s] Detached Mux From Aggregator\n",
			     bondport_get_name(p));
	}
	bondport_flags_clear_mux_attached(p);
    }
    return;
}