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
struct quotafile {int qf_qflags; } ;

/* Variables and functions */
#define  QTF_CLOSING 129 
#define  QTF_OPENING 128 
 int QTF_WANTED ; 
 int /*<<< orphan*/  dq_list_lock () ; 
 int /*<<< orphan*/  dq_list_unlock () ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
qf_put(struct quotafile *qfp, int type)
{

        dq_list_lock();

        switch (type) {

	case QTF_OPENING:
	case QTF_CLOSING:
	        qfp->qf_qflags &= ~type;
		break;
	}
	if ( (qfp->qf_qflags & QTF_WANTED) ) {
	        qfp->qf_qflags &= ~QTF_WANTED;
		wakeup(&qfp->qf_qflags);
	}
	dq_list_unlock();
}