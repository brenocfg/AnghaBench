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
struct p9_trans_fd {TYPE_1__* rd; } ;
struct p9_client {scalar_t__ status; struct p9_trans_fd* trans; } ;
struct TYPE_2__ {int f_flags; int /*<<< orphan*/  f_pos; } ;

/* Variables and functions */
 scalar_t__ Disconnected ; 
 int EAGAIN ; 
 int EREMOTEIO ; 
 int ERESTARTSYS ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int kernel_read (TYPE_1__*,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int p9_fd_read(struct p9_client *client, void *v, int len)
{
	int ret;
	struct p9_trans_fd *ts = NULL;

	if (client && client->status != Disconnected)
		ts = client->trans;

	if (!ts)
		return -EREMOTEIO;

	if (!(ts->rd->f_flags & O_NONBLOCK))
		P9_DPRINTK(P9_DEBUG_ERROR, "blocking read ...\n");

	ret = kernel_read(ts->rd, ts->rd->f_pos, v, len);
	if (ret <= 0 && ret != -ERESTARTSYS && ret != -EAGAIN)
		client->status = Disconnected;
	return ret;
}