#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_pageio_descriptor {TYPE_2__* pg_lseg; } ;
struct nfs_page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {TYPE_1__ pls_range; } ;

/* Variables and functions */
 scalar_t__ end_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs_generic_pg_test (struct nfs_pageio_descriptor*,struct nfs_page*,struct nfs_page*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 

bool
pnfs_generic_pg_test(struct nfs_pageio_descriptor *pgio, struct nfs_page *prev,
		     struct nfs_page *req)
{
	if (pgio->pg_lseg == NULL)
		return nfs_generic_pg_test(pgio, prev, req);

	/*
	 * Test if a nfs_page is fully contained in the pnfs_layout_range.
	 * Note that this test makes several assumptions:
	 * - that the previous nfs_page in the struct nfs_pageio_descriptor
	 *   is known to lie within the range.
	 *   - that the nfs_page being tested is known to be contiguous with the
	 *   previous nfs_page.
	 *   - Layout ranges are page aligned, so we only have to test the
	 *   start offset of the request.
	 *
	 * Please also note that 'end_offset' is actually the offset of the
	 * first byte that lies outside the pnfs_layout_range. FIXME?
	 *
	 */
	return req_offset(req) < end_offset(pgio->pg_lseg->pls_range.offset,
					 pgio->pg_lseg->pls_range.length);
}