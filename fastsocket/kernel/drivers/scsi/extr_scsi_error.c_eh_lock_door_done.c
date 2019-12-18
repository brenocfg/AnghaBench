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
struct request {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  __blk_put_request (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static void eh_lock_door_done(struct request *req, int uptodate)
{
	__blk_put_request(req->q, req);
}