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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  __blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 scalar_t__ __send_request (struct request*) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 

__attribute__((used)) static void do_vdc_request(struct request_queue *q)
{
	while (1) {
		struct request *req = blk_fetch_request(q);

		if (!req)
			break;

		if (__send_request(req) < 0)
			__blk_end_request_all(req, -EIO);
	}
}