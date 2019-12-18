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
struct callstack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_CS_KDATA ; 
 int /*<<< orphan*/  PERF_CS_KHDR ; 
 int /*<<< orphan*/  callstack_log (struct callstack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kperf_kcallstack_log( struct callstack *cs )
{
	callstack_log(cs, PERF_CS_KHDR, PERF_CS_KDATA);
}