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
struct rndis_indicate_status {scalar_t__ status; } ;
struct TYPE_3__ {struct rndis_indicate_status indicate_status; } ;
struct rndis_message {TYPE_1__ msg; } ;
struct rndis_device {TYPE_2__* net_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ RNDIS_STATUS_MEDIA_CONNECT ; 
 scalar_t__ RNDIS_STATUS_MEDIA_DISCONNECT ; 
 int /*<<< orphan*/  netvsc_linkstatus_callback (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rndis_filter_receive_indicate_status(struct rndis_device *dev,
					     struct rndis_message *resp)
{
	struct rndis_indicate_status *indicate =
			&resp->msg.indicate_status;

	if (indicate->status == RNDIS_STATUS_MEDIA_CONNECT) {
		netvsc_linkstatus_callback(
			dev->net_dev->dev, 1);
	} else if (indicate->status == RNDIS_STATUS_MEDIA_DISCONNECT) {
		netvsc_linkstatus_callback(
			dev->net_dev->dev, 0);
	} else {
		/*
		 * TODO:
		 */
	}
}