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
typedef  enum fip_state { ____Placeholder_fip_state } fip_state ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_CREATE_LINK_UP ; 
 int _bnx2fc_create (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2fc_create(struct net_device *netdev, enum fip_state fip_mode)
{
	return _bnx2fc_create(netdev, fip_mode, BNX2FC_CREATE_LINK_UP);
}