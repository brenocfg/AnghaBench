#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_4__ sin_addr; } ;
struct dst_entry {int dummy; } ;
struct TYPE_5__ {struct dst_entry dst; } ;
struct rtable {TYPE_1__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_7__ {TYPE_2__ ip4_u; } ;
struct flowi {TYPE_3__ nl_u; } ;
typedef  int /*<<< orphan*/  fl ;

/* Variables and functions */
 int ENETUNREACH ; 
 int /*<<< orphan*/  init_net ; 
 int ip_route_output_key (int /*<<< orphan*/ *,struct rtable**,struct flowi*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cnic_get_v4_route(struct sockaddr_in *dst_addr,
			     struct dst_entry **dst)
{
#if defined(CONFIG_INET)
	struct flowi fl;
	int err;
	struct rtable *rt;

	memset(&fl, 0, sizeof(fl));
	fl.nl_u.ip4_u.daddr = dst_addr->sin_addr.s_addr;

	err = ip_route_output_key(&init_net, &rt, &fl);
	if (!err)
		*dst = &rt->u.dst;
	return err;
#else
	return -ENETUNREACH;
#endif
}