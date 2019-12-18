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
struct dm_ulog_request {scalar_t__ data_size; int /*<<< orphan*/  seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;
struct cn_msg {scalar_t__ len; int /*<<< orphan*/  seq; scalar_t__ ack; TYPE_1__ id; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int cn_netlink_send (struct cn_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfp_any () ; 
 int /*<<< orphan*/  memset (struct cn_msg*,int /*<<< orphan*/ ,int) ; 
 struct cn_msg* prealloced_cn_msg ; 
 TYPE_2__ ulog_cn_id ; 

__attribute__((used)) static int dm_ulog_sendto_server(struct dm_ulog_request *tfr)
{
	int r;
	struct cn_msg *msg = prealloced_cn_msg;

	memset(msg, 0, sizeof(struct cn_msg));

	msg->id.idx = ulog_cn_id.idx;
	msg->id.val = ulog_cn_id.val;
	msg->ack = 0;
	msg->seq = tfr->seq;
	msg->len = sizeof(struct dm_ulog_request) + tfr->data_size;

	r = cn_netlink_send(msg, 0, gfp_any());

	return r;
}