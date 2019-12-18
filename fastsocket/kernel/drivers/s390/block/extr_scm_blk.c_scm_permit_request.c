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
struct scm_blk_dev {scalar_t__ state; } ;
struct request {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCM_WR_PROHIBIT ; 
 scalar_t__ WRITE ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static bool scm_permit_request(struct scm_blk_dev *bdev, struct request *req)
{
	return rq_data_dir(req) != WRITE || bdev->state != SCM_WR_PROHIBIT;
}