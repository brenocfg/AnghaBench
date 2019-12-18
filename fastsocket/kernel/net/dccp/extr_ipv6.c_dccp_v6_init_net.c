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
struct TYPE_2__ {int /*<<< orphan*/  v6_ctl_sk; } ;
struct net {TYPE_1__ dccp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_DCCP ; 
 int inet_ctl_sock_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*) ; 

__attribute__((used)) static int dccp_v6_init_net(struct net *net)
{
	int err;

	err = inet_ctl_sock_create(&net->dccp.v6_ctl_sk, PF_INET6,
				   SOCK_DCCP, IPPROTO_DCCP, net);
	return err;
}