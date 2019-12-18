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
struct quotafile {scalar_t__ qf_refcnt; int qf_qflags; } ;

/* Variables and functions */
 int QTF_WANTED ; 
 int /*<<< orphan*/  wakeup (int*) ; 

__attribute__((used)) static void
qf_rele(struct quotafile *qfp)
{
	qfp->qf_refcnt--;

	if ( (qfp->qf_qflags & QTF_WANTED) && qfp->qf_refcnt == 0) {
	        qfp->qf_qflags &= ~QTF_WANTED;
	        wakeup(&qfp->qf_qflags);
	}
}