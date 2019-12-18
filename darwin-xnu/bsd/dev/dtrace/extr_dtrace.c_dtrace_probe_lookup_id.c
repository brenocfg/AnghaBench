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
typedef  int /*<<< orphan*/  dtrace_probe_t ;
typedef  int dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  dtrace_lock ; 
 scalar_t__ dtrace_nprobes ; 
 int /*<<< orphan*/ ** dtrace_probes ; 

__attribute__((used)) static dtrace_probe_t *
dtrace_probe_lookup_id(dtrace_id_t id)
{
	LCK_MTX_ASSERT(&dtrace_lock, LCK_MTX_ASSERT_OWNED);

	if (id == 0 || id > (dtrace_id_t)dtrace_nprobes)
		return (NULL);

	return (dtrace_probes[id - 1]);
}