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
struct nfsd3_fhandle_pair {int /*<<< orphan*/  fh2; int /*<<< orphan*/  fh1; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 

int
nfs3svc_release_fhandle2(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_fhandle_pair *resp)
{
	fh_put(&resp->fh1);
	fh_put(&resp->fh2);
	return 1;
}