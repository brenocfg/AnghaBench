#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int u_int32_t ;
struct sockaddr {int sa_len; } ;
struct rtentry {int /*<<< orphan*/  rt_flags; TYPE_3__* rt_ifp; struct sockaddr* rt_gateway; struct rtentry* rt_gwroute; struct rtentry* rt_parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  sa; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  ifindex; TYPE_2__ gateway; int /*<<< orphan*/  mask; TYPE_1__ dst; void* gateway_id; void* parent_id; void* id; } ;
typedef  TYPE_4__ nstat_route_descriptor ;
typedef  scalar_t__ nstat_provider_cookie_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_8__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct rtentry*) ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 int /*<<< orphan*/  nstat_copy_sa_out (struct sockaddr*,int /*<<< orphan*/ *,int) ; 
 struct sockaddr* rt_key (struct rtentry*) ; 
 struct sockaddr* rt_mask (struct rtentry*) ; 

__attribute__((used)) static errno_t
nstat_route_copy_descriptor(
	nstat_provider_cookie_t	cookie,
	void					*data,
	u_int32_t				len)
{
	nstat_route_descriptor	*desc = (nstat_route_descriptor*)data;
	if (len < sizeof(*desc))
	{
		return EINVAL;
	}
	bzero(desc, sizeof(*desc));

	struct rtentry	*rt = (struct rtentry*)cookie;
	desc->id = (uint64_t)VM_KERNEL_ADDRPERM(rt);
	desc->parent_id = (uint64_t)VM_KERNEL_ADDRPERM(rt->rt_parent);
	desc->gateway_id = (uint64_t)VM_KERNEL_ADDRPERM(rt->rt_gwroute);


	// key/dest
	struct sockaddr	*sa;
	if ((sa = rt_key(rt)))
		nstat_copy_sa_out(sa, &desc->dst.sa, sizeof(desc->dst));

	// mask
	if ((sa = rt_mask(rt)) && sa->sa_len <= sizeof(desc->mask))
		memcpy(&desc->mask, sa, sa->sa_len);

	// gateway
	if ((sa = rt->rt_gateway))
		nstat_copy_sa_out(sa, &desc->gateway.sa, sizeof(desc->gateway));

	if (rt->rt_ifp)
		desc->ifindex = rt->rt_ifp->if_index;

	desc->flags = rt->rt_flags;

	return 0;
}