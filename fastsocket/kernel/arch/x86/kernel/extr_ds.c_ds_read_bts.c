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
struct bts_trace {int /*<<< orphan*/  ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;
struct bts_tracer {struct bts_trace const trace; TYPE_1__ ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds_bts ; 
 int /*<<< orphan*/  ds_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const struct bts_trace *ds_read_bts(struct bts_tracer *tracer)
{
	if (!tracer)
		return NULL;

	ds_read_config(tracer->ds.context, &tracer->trace.ds, ds_bts);
	return &tracer->trace;
}