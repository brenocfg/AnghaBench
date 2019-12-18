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
struct TYPE_2__ {int /*<<< orphan*/  v4_ctl_sk; } ;
struct net {TYPE_1__ dccp; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_ctl_sock_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_v4_exit_net(struct net *net)
{
	inet_ctl_sock_destroy(net->dccp.v4_ctl_sk);
}