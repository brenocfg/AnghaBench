#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ top; scalar_t__ begin; } ;
struct TYPE_8__ {TYPE_3__ ds; } ;
struct TYPE_6__ {TYPE_1__* context; } ;
struct bts_tracer {TYPE_4__ trace; TYPE_2__ ds; } ;
struct TYPE_5__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ds_bts ; 
 int /*<<< orphan*/  ds_index ; 
 int /*<<< orphan*/  ds_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

int ds_reset_bts(struct bts_tracer *tracer)
{
	if (!tracer)
		return -EINVAL;

	tracer->trace.ds.top = tracer->trace.ds.begin;

	ds_set(tracer->ds.context->ds, ds_bts, ds_index,
	       (unsigned long)tracer->trace.ds.top);

	return 0;
}