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
typedef  int /*<<< orphan*/  u64 ;
struct cfq_rb_root {int /*<<< orphan*/  min_vdisktime; scalar_t__ left; scalar_t__ active; } ;
struct cfq_group {int /*<<< orphan*/  vdisktime; } ;

/* Variables and functions */
 int /*<<< orphan*/  max_vdisktime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_vdisktime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfq_group* rb_entry_cfqg (scalar_t__) ; 

__attribute__((used)) static void update_min_vdisktime(struct cfq_rb_root *st)
{
	u64 vdisktime = st->min_vdisktime;
	struct cfq_group *cfqg;

	if (st->active) {
		cfqg = rb_entry_cfqg(st->active);
		vdisktime = cfqg->vdisktime;
	}

	if (st->left) {
		cfqg = rb_entry_cfqg(st->left);
		vdisktime = min_vdisktime(vdisktime, cfqg->vdisktime);
	}

	st->min_vdisktime = max_vdisktime(st->min_vdisktime, vdisktime);
}