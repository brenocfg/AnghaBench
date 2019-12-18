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
struct svc_rqst {int dummy; } ;
struct nlm_host {int dummy; } ;
struct nlm_args {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_release_host (struct nlm_host*) ; 
 int /*<<< orphan*/  nlmsvc_free_host_resources (struct nlm_host*) ; 
 scalar_t__ nlmsvc_retrieve_args (struct svc_rqst*,struct nlm_args*,struct nlm_host**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_success ; 

__attribute__((used)) static __be32
nlmsvc_proc_free_all(struct svc_rqst *rqstp, struct nlm_args *argp,
					     void            *resp)
{
	struct nlm_host	*host;

	/* Obtain client */
	if (nlmsvc_retrieve_args(rqstp, argp, &host, NULL))
		return rpc_success;

	nlmsvc_free_host_resources(host);
	nlm_release_host(host);
	return rpc_success;
}