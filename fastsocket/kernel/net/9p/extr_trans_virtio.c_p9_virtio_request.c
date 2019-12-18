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
struct virtio_chan {int /*<<< orphan*/  vq; int /*<<< orphan*/  sg; } ;
struct p9_req_t {TYPE_1__* tc; int /*<<< orphan*/  status; scalar_t__ rc; } ;
struct p9_fcall {int dummy; } ;
struct p9_client {int /*<<< orphan*/  msize; struct virtio_chan* trans; } ;
struct TYPE_2__ {char* sdata; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  P9_DEBUG_TRANS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REQ_STATUS_SENT ; 
 scalar_t__ VIRTQUEUE_NUM ; 
 int pack_sg_list (int /*<<< orphan*/ ,int,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ virtqueue_add_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
p9_virtio_request(struct p9_client *client, struct p9_req_t *req)
{
	int in, out;
	struct virtio_chan *chan = client->trans;
	char *rdata = (char *)req->rc+sizeof(struct p9_fcall);

	P9_DPRINTK(P9_DEBUG_TRANS, "9p debug: virtio request\n");

	out = pack_sg_list(chan->sg, 0, VIRTQUEUE_NUM, req->tc->sdata,
								req->tc->size);
	in = pack_sg_list(chan->sg, out, VIRTQUEUE_NUM-out, rdata,
								client->msize);

	req->status = REQ_STATUS_SENT;

	if (virtqueue_add_buf(chan->vq, chan->sg, out, in, req->tc) < 0) {
		P9_DPRINTK(P9_DEBUG_TRANS,
			"9p debug: virtio rpc add_buf returned failure");
		return -EIO;
	}

	virtqueue_kick(chan->vq);

	P9_DPRINTK(P9_DEBUG_TRANS, "9p debug: virtio request kicked\n");
	return 0;
}