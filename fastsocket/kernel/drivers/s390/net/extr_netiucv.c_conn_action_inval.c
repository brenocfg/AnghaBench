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
struct net_device {int /*<<< orphan*/  name; } ;
struct iucv_connection {int /*<<< orphan*/  userid; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  IUCV_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 

__attribute__((used)) static void conn_action_inval(fsm_instance *fi, int event, void *arg)
{
	struct iucv_connection *conn = arg;
	struct net_device *netdev = conn->netdev;

	IUCV_DBF_TEXT_(data, 2, "%s('%s'): conn_action_inval called\n",
		netdev->name, conn->userid);
}