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
struct TYPE_2__ {struct kvec* head; } ;
struct svc_rqst {TYPE_1__ rq_res; } ;
struct kvec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  svc_putnl (struct kvec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svc_tcp_prep_reply_hdr(struct svc_rqst *rqstp)
{
	struct kvec *resv = &rqstp->rq_res.head[0];

	/* tcp needs a space for the record length... */
	svc_putnl(resv, 0);
}