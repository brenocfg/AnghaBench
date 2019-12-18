#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsrec_t ;
struct TYPE_4__ {int lsd_count; int /*<<< orphan*/ * lsd_next; } ;
typedef  TYPE_1__ lsdata_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  dfail (char*) ; 
 scalar_t__ dtrace_aggregate_walk_keyvarsorted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ dtrace_consume (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  g_dtp ; 
 scalar_t__ g_tracing ; 
 int /*<<< orphan*/  process_aggregate ; 
 int /*<<< orphan*/  process_trace ; 

__attribute__((used)) static int
process_data(FILE *out, char *data)
{
	lsdata_t lsdata;

	/* LINTED - alignment */
	lsdata.lsd_next = (lsrec_t *)data;
	lsdata.lsd_count = 0;

	if (g_tracing) {
		if (dtrace_consume(g_dtp, out,
		    process_trace, NULL, &lsdata) != 0)
			dfail("failed to consume buffer");

		return (lsdata.lsd_count);
	}

	if (dtrace_aggregate_walk_keyvarsorted(g_dtp,
	    process_aggregate, &lsdata) != 0)
		dfail("failed to walk aggregate");

	return (lsdata.lsd_count);
}