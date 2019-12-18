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
struct nfsd4_lookup {int /*<<< orphan*/  lo_len; int /*<<< orphan*/  lo_name; } ;
struct nfsd4_compound_state {int /*<<< orphan*/  current_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  nfsd_lookup (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_lookup(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	     struct nfsd4_lookup *lookup)
{
	return nfsd_lookup(rqstp, &cstate->current_fh,
			   lookup->lo_name, lookup->lo_len,
			   &cstate->current_fh);
}