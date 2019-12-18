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
struct request {int dummy; } ;

/* Variables and functions */
 int __blk_end_request (struct request*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_cur_bytes (struct request*) ; 

bool __blk_end_request_cur(struct request *rq, int error)
{
	return __blk_end_request(rq, error, blk_rq_cur_bytes(rq));
}