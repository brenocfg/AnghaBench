#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct pcd_unit {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  buffer; TYPE_1__* rq_disk; } ;
struct TYPE_8__ {struct pcd_unit* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  __blk_end_request_all (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_rq_cur_sectors (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_rq_pos (TYPE_2__*) ; 
 int /*<<< orphan*/  do_pcd_read ; 
 int /*<<< orphan*/  nice ; 
 int /*<<< orphan*/  pcd_buf ; 
 int pcd_bufblk ; 
 int pcd_busy ; 
 int /*<<< orphan*/  pcd_count ; 
 struct pcd_unit* pcd_current ; 
 TYPE_2__* pcd_req ; 
 int /*<<< orphan*/  pcd_sector ; 
 int /*<<< orphan*/  ps_set_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rq_data_dir (TYPE_2__*) ; 

__attribute__((used)) static void do_pcd_request(struct request_queue * q)
{
	if (pcd_busy)
		return;
	while (1) {
		if (!pcd_req) {
			pcd_req = blk_fetch_request(q);
			if (!pcd_req)
				return;
		}

		if (rq_data_dir(pcd_req) == READ) {
			struct pcd_unit *cd = pcd_req->rq_disk->private_data;
			if (cd != pcd_current)
				pcd_bufblk = -1;
			pcd_current = cd;
			pcd_sector = blk_rq_pos(pcd_req);
			pcd_count = blk_rq_cur_sectors(pcd_req);
			pcd_buf = pcd_req->buffer;
			pcd_busy = 1;
			ps_set_intr(do_pcd_read, NULL, 0, nice);
			return;
		} else {
			__blk_end_request_all(pcd_req, -EIO);
			pcd_req = NULL;
		}
	}
}