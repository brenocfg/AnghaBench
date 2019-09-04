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
struct quotafile {int qf_qflags; scalar_t__ qf_vp; int /*<<< orphan*/  qf_refcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NULLVP ; 
 int QTF_CLOSING ; 
 int QTF_OPENING ; 

__attribute__((used)) static int
qf_ref(struct quotafile *qfp)
{
        int error = 0;

	if ( (qfp->qf_qflags & (QTF_OPENING | QTF_CLOSING)) || (qfp->qf_vp == NULLVP) )
	        error = EINVAL;
	else
	        qfp->qf_refcnt++;

	return (error);
}