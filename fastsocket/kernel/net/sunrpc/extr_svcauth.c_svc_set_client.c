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
struct svc_rqst {TYPE_1__* rq_authop; } ;
struct TYPE_2__ {int (* set_client ) (struct svc_rqst*) ;} ;

/* Variables and functions */
 int stub1 (struct svc_rqst*) ; 

int svc_set_client(struct svc_rqst *rqstp)
{
	return rqstp->rq_authop->set_client(rqstp);
}