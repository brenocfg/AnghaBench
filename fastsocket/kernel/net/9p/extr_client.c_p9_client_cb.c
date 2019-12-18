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
struct p9_req_t {TYPE_1__* tc; int /*<<< orphan*/  wq; } ;
struct p9_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_MUX ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ ) ; 

void p9_client_cb(struct p9_client *c, struct p9_req_t *req)
{
	P9_DPRINTK(P9_DEBUG_MUX, " tag %d\n", req->tc->tag);
	wake_up(req->wq);
	P9_DPRINTK(P9_DEBUG_MUX, "wakeup: %d\n", req->tc->tag);
}