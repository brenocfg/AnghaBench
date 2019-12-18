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
struct svc_rqst {struct auth_domain* rq_client; struct auth_domain* rq_gssclient; } ;
struct auth_domain {char* name; } ;

/* Variables and functions */

__attribute__((used)) static char *
rqst_authname(struct svc_rqst *rqstp)
{
	struct auth_domain *clp;

	clp = rqstp->rq_gssclient ? rqstp->rq_gssclient : rqstp->rq_client;
	return clp->name;
}