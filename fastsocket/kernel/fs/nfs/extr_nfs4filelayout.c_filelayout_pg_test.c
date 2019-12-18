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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfs_pageio_descriptor {int /*<<< orphan*/  pg_lseg; } ;
struct nfs_page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stripe_unit; } ;

/* Variables and functions */
 TYPE_1__* FILELAYOUT_LSEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_generic_pg_test (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ; 
 int /*<<< orphan*/  pnfs_generic_pg_test (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 

__attribute__((used)) static bool
filelayout_pg_test(struct nfs_pageio_descriptor *pgio, struct nfs_page *prev,
		   struct nfs_page *req)
{
	u64 p_stripe, r_stripe;
	u32 stripe_unit;

	if (!pnfs_generic_pg_test(pgio, prev, req) ||
	    !nfs_generic_pg_test(pgio, prev, req))
		return false;

	p_stripe = (u64)req_offset(prev);
	r_stripe = (u64)req_offset(req);
	stripe_unit = FILELAYOUT_LSEG(pgio->pg_lseg)->stripe_unit;

	do_div(p_stripe, stripe_unit);
	do_div(r_stripe, stripe_unit);

	return (p_stripe == r_stripe);
}