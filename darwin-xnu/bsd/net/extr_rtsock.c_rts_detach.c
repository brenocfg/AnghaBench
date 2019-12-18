#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct TYPE_4__ {int sp_protocol; } ;
struct rawcb {TYPE_1__ rcb_proto; } ;
struct TYPE_6__ {int (* pru_detach ) (struct socket*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  any_count; int /*<<< orphan*/  ip6_count; int /*<<< orphan*/  ip_count; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 TYPE_3__ raw_usrreqs ; 
 TYPE_2__ route_cb ; 
 struct rawcb* sotorawcb (struct socket*) ; 
 int stub1 (struct socket*) ; 

__attribute__((used)) static int
rts_detach(struct socket *so)
{
	struct rawcb *rp = sotorawcb(so);

	VERIFY(rp != NULL);

	switch (rp->rcb_proto.sp_protocol) {
	case AF_INET:
		atomic_add_32(&route_cb.ip_count, -1);
		break;
	case AF_INET6:
		atomic_add_32(&route_cb.ip6_count, -1);
		break;
	}
	atomic_add_32(&route_cb.any_count, -1);
	return (raw_usrreqs.pru_detach(so));
}