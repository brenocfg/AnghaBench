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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct av7110 {int (* fe_read_status ) (struct dvb_frontend*,int*) ;int fe_status; } ;
typedef  int fe_status_t ;
struct TYPE_2__ {struct av7110* priv; } ;

/* Variables and functions */
 int FE_HAS_LOCK ; 
 int av7110_fe_lock_fix (struct av7110*,int) ; 
 int stub1 (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int av7110_fe_read_status(struct dvb_frontend* fe, fe_status_t* status)
{
	struct av7110* av7110 = fe->dvb->priv;

	/* call the real implementation */
	int ret = av7110->fe_read_status(fe, status);
	if (!ret)
		if (((*status ^ av7110->fe_status) & FE_HAS_LOCK) && (*status & FE_HAS_LOCK))
			ret = av7110_fe_lock_fix(av7110, *status);
	return ret;
}