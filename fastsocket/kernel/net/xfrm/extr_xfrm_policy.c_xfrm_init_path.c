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
struct xfrm_policy_afinfo {int (* init_path ) (struct xfrm_dst*,struct dst_entry*,int) ;} ;
struct xfrm_dst {int dummy; } ;
struct dst_entry {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct xfrm_dst*,struct dst_entry*,int) ; 
 struct xfrm_policy_afinfo* xfrm_policy_get_afinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfrm_policy_put_afinfo (struct xfrm_policy_afinfo*) ; 

__attribute__((used)) static inline int xfrm_init_path(struct xfrm_dst *path, struct dst_entry *dst,
				 int nfheader_len)
{
	struct xfrm_policy_afinfo *afinfo =
		xfrm_policy_get_afinfo(dst->ops->family);
	int err;

	if (!afinfo)
		return -EINVAL;

	err = afinfo->init_path(path, dst, nfheader_len);

	xfrm_policy_put_afinfo(afinfo);

	return err;
}