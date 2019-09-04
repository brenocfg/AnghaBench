#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dtpr_id; } ;
typedef  TYPE_1__ dtrace_probe_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int DTRACE_MATCH_DONE ; 

__attribute__((used)) static int
dtrace_probe_lookup_match(dtrace_probe_t *probe, void *arg1, void *arg2)
{
#pragma unused(arg2)
	*((dtrace_id_t *)arg1) = probe->dtpr_id;

	return (DTRACE_MATCH_DONE);
}