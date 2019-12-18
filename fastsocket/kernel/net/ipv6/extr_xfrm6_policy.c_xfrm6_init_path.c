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
struct TYPE_7__ {int rt6i_nfheader_len; } ;
struct TYPE_8__ {TYPE_3__ rt6; } ;
struct xfrm_dst {TYPE_4__ u; int /*<<< orphan*/  path_cookie; } ;
struct rt6_info {TYPE_2__* rt6i_node; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  fn_sernum; } ;
struct TYPE_5__ {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 

__attribute__((used)) static int xfrm6_init_path(struct xfrm_dst *path, struct dst_entry *dst,
			   int nfheader_len)
{
	if (dst->ops->family == AF_INET6) {
		struct rt6_info *rt = (struct rt6_info*)dst;
		if (rt->rt6i_node)
			path->path_cookie = rt->rt6i_node->fn_sernum;
	}

	path->u.rt6.rt6i_nfheader_len = nfheader_len;

	return 0;
}