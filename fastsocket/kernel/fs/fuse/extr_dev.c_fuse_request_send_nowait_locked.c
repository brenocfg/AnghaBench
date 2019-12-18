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
struct fuse_req {int background; int /*<<< orphan*/  list; } ;
struct fuse_conn {scalar_t__ num_background; scalar_t__ max_background; int blocked; scalar_t__ congestion_threshold; int /*<<< orphan*/  bg_queue; int /*<<< orphan*/  bdi; scalar_t__ bdi_initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int /*<<< orphan*/  BLK_RW_SYNC ; 
 int /*<<< orphan*/  flush_bg_queue (struct fuse_conn*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bdi_congested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fuse_request_send_nowait_locked(struct fuse_conn *fc,
					    struct fuse_req *req)
{
	req->background = 1;
	fc->num_background++;
	if (fc->num_background == fc->max_background)
		fc->blocked = 1;
	if (fc->num_background == fc->congestion_threshold &&
	    fc->bdi_initialized) {
		set_bdi_congested(&fc->bdi, BLK_RW_SYNC);
		set_bdi_congested(&fc->bdi, BLK_RW_ASYNC);
	}
	list_add_tail(&req->list, &fc->bg_queue);
	flush_bg_queue(fc);
}