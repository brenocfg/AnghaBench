#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  context; } ;
struct bts_tracer {TYPE_4__ ds; } ;
struct TYPE_7__ {int clock; int pid; } ;
struct TYPE_6__ {int from; int to; } ;
struct TYPE_8__ {TYPE_2__ event; TYPE_1__ lbr; } ;
struct bts_struct {int qualifier; TYPE_3__ variant; } ;
struct TYPE_10__ {int* sizeof_rec; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int MAX_SIZEOF_BTS ; 
#define  bts_branch 131 
 int /*<<< orphan*/  bts_clock ; 
 int bts_escape ; 
 int /*<<< orphan*/  bts_flags ; 
 int /*<<< orphan*/  bts_from ; 
#define  bts_invalid 130 
 int /*<<< orphan*/  bts_pid ; 
 int /*<<< orphan*/  bts_qual ; 
 int /*<<< orphan*/  bts_set (unsigned char*,int /*<<< orphan*/ ,int) ; 
#define  bts_task_arrives 129 
#define  bts_task_departs 128 
 int /*<<< orphan*/  bts_to ; 
 size_t ds_bts ; 
 TYPE_5__ ds_cfg ; 
 int ds_write (int /*<<< orphan*/ ,size_t,unsigned char*,int) ; 

__attribute__((used)) static int bts_write(struct bts_tracer *tracer, const struct bts_struct *in)
{
	unsigned char raw[MAX_SIZEOF_BTS];

	if (!tracer)
		return -EINVAL;

	if (MAX_SIZEOF_BTS < ds_cfg.sizeof_rec[ds_bts])
		return -EOVERFLOW;

	switch (in->qualifier) {
	case bts_invalid:
		bts_set(raw, bts_from, 0);
		bts_set(raw, bts_to, 0);
		bts_set(raw, bts_flags, 0);
		break;
	case bts_branch:
		bts_set(raw, bts_from, in->variant.lbr.from);
		bts_set(raw, bts_to,   in->variant.lbr.to);
		bts_set(raw, bts_flags, 0);
		break;
	case bts_task_arrives:
	case bts_task_departs:
		bts_set(raw, bts_qual, (bts_escape | in->qualifier));
		bts_set(raw, bts_clock, in->variant.event.clock);
		bts_set(raw, bts_pid, in->variant.event.pid);
		break;
	default:
		return -EINVAL;
	}

	return ds_write(tracer->ds.context, ds_bts, raw,
			ds_cfg.sizeof_rec[ds_bts]);
}