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

/* Variables and functions */
 int /*<<< orphan*/  dfail (char*) ; 
 scalar_t__ dtrace_aggregate_snap (int /*<<< orphan*/ ) ; 
 int dtrace_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_dtp ; 
 int /*<<< orphan*/  g_tracing ; 

__attribute__((used)) static void
status_check(void)
{
	if (!g_tracing && dtrace_aggregate_snap(g_dtp) != 0)
		dfail("failed to snap aggregate");

	if (dtrace_status(g_dtp) == -1)
		dfail("dtrace_status()");
}