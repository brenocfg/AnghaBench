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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COUNT_HW_MAX ; 
 int /*<<< orphan*/  PERF_COUNT_SW_MAX ; 
 scalar_t__ PERF_TYPE_SOFTWARE ; 
 int /*<<< orphan*/  __print_events_type (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_symbols_hw ; 
 int /*<<< orphan*/  event_symbols_sw ; 

void print_events_type(u8 type)
{
	if (type == PERF_TYPE_SOFTWARE)
		__print_events_type(type, event_symbols_sw, PERF_COUNT_SW_MAX);
	else
		__print_events_type(type, event_symbols_hw, PERF_COUNT_HW_MAX);
}