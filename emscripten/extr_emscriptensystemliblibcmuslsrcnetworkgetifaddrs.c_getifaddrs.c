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
struct ifaddrs_ctx {TYPE_1__* first; } ;
struct ifaddrs {int dummy; } ;
struct TYPE_2__ {struct ifaddrs ifa; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int __rtnetlink_enumerate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifaddrs_ctx*) ; 
 int /*<<< orphan*/  freeifaddrs (struct ifaddrs*) ; 
 int /*<<< orphan*/  memset (struct ifaddrs_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netlink_msg_to_ifaddr ; 

int getifaddrs(struct ifaddrs **ifap)
{
	struct ifaddrs_ctx _ctx, *ctx = &_ctx;
	int r;
	memset(ctx, 0, sizeof *ctx);
	r = __rtnetlink_enumerate(AF_UNSPEC, AF_UNSPEC, netlink_msg_to_ifaddr, ctx);
	if (r == 0) *ifap = &ctx->first->ifa;
	else freeifaddrs(&ctx->first->ifa);
	return r;
}