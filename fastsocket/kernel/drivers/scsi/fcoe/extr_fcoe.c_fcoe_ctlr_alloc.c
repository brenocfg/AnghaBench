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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_CREATE_LINK_DOWN ; 
 int /*<<< orphan*/  FIP_MODE_FABRIC ; 
 int _fcoe_create (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fcoe_ctlr_alloc(struct net_device *netdev)
{
	return _fcoe_create(netdev, FIP_MODE_FABRIC,
			    FCOE_CREATE_LINK_DOWN);
}