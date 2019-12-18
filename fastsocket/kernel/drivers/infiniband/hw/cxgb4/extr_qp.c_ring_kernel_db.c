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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
struct c4iw_qp {TYPE_4__* rhp; TYPE_3__ wq; } ;
struct TYPE_5__ {int dbfifo_int_thresh; int /*<<< orphan*/ * ports; } ;
struct TYPE_6__ {TYPE_1__ lldi; } ;
struct TYPE_8__ {int /*<<< orphan*/  db_mutex; TYPE_2__ rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int V_PIDX (int /*<<< orphan*/ ) ; 
 int V_QID (int /*<<< orphan*/ ) ; 
 int cxgb4_dbfifo_count (int /*<<< orphan*/ ,int) ; 
 int db_delay_usecs ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ring_kernel_db(struct c4iw_qp *qhp, u32 qid, u16 inc)
{
	int delay = db_delay_usecs;

	mutex_lock(&qhp->rhp->db_mutex);
	do {

		/*
		 * The interrupt threshold is dbfifo_int_thresh << 6. So
		 * make sure we don't cross that and generate an interrupt.
		 */
		if (cxgb4_dbfifo_count(qhp->rhp->rdev.lldi.ports[0], 1) <
		    (qhp->rhp->rdev.lldi.dbfifo_int_thresh << 5)) {
			writel(V_QID(qid) | V_PIDX(inc), qhp->wq.db);
			break;
		}
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(usecs_to_jiffies(delay));
		delay = min(delay << 1, 2000);
	} while (1);
	mutex_unlock(&qhp->rhp->db_mutex);
	return 0;
}