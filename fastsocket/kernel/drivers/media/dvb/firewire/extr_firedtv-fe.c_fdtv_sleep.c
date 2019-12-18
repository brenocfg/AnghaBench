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
struct firedtv {int isochannel; int /*<<< orphan*/  subunit; TYPE_1__* backend; } ;
struct dvb_frontend {struct firedtv* sec_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_iso ) (struct firedtv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_break_pp_connection (struct firedtv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct firedtv*) ; 

__attribute__((used)) static int fdtv_sleep(struct dvb_frontend *fe)
{
	struct firedtv *fdtv = fe->sec_priv;

	fdtv->backend->stop_iso(fdtv);
	cmp_break_pp_connection(fdtv, fdtv->subunit, fdtv->isochannel);
	fdtv->isochannel = -1;
	return 0;
}