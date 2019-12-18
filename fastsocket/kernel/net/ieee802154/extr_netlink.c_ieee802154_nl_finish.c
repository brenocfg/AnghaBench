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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NLMSG_DATA (int /*<<< orphan*/ ) ; 
 void* genlmsg_data (int /*<<< orphan*/ ) ; 
 scalar_t__ genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_multicast (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ ieee802154_coord_mcgrp ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 

__attribute__((used)) static int ieee802154_nl_finish(struct sk_buff *msg)
{
	/* XXX: nlh is right at the start of msg */
	void *hdr = genlmsg_data(NLMSG_DATA(msg->data));

	if (genlmsg_end(msg, hdr) < 0)
		goto out;

	return genlmsg_multicast(msg, 0, ieee802154_coord_mcgrp.id,
			GFP_ATOMIC);
out:
	nlmsg_free(msg);
	return -ENOBUFS;
}