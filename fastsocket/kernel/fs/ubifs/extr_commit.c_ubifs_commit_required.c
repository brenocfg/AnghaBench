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
struct ubifs_info {int cmt_state; int /*<<< orphan*/  cs_lock; } ;

/* Variables and functions */
#define  COMMIT_BACKGROUND 133 
#define  COMMIT_BROKEN 132 
#define  COMMIT_REQUIRED 131 
#define  COMMIT_RESTING 130 
#define  COMMIT_RUNNING_BACKGROUND 129 
#define  COMMIT_RUNNING_REQUIRED 128 
 int /*<<< orphan*/  dbg_cmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_cstate (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ubifs_commit_required(struct ubifs_info *c)
{
	spin_lock(&c->cs_lock);
	switch (c->cmt_state) {
	case COMMIT_RESTING:
	case COMMIT_BACKGROUND:
		dbg_cmt("old: %s, new: %s", dbg_cstate(c->cmt_state),
			dbg_cstate(COMMIT_REQUIRED));
		c->cmt_state = COMMIT_REQUIRED;
		break;
	case COMMIT_RUNNING_BACKGROUND:
		dbg_cmt("old: %s, new: %s", dbg_cstate(c->cmt_state),
			dbg_cstate(COMMIT_RUNNING_REQUIRED));
		c->cmt_state = COMMIT_RUNNING_REQUIRED;
		break;
	case COMMIT_REQUIRED:
	case COMMIT_RUNNING_REQUIRED:
	case COMMIT_BROKEN:
		break;
	}
	spin_unlock(&c->cs_lock);
}