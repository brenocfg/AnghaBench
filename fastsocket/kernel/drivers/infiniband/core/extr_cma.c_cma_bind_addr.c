#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; } ;
struct sockaddr_ib {int /*<<< orphan*/  sib_pkey; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  src_addr; } ;
struct TYPE_3__ {TYPE_2__ addr; } ;
struct rdma_cm_id {TYPE_1__ route; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 scalar_t__ AF_INET6 ; 
 int rdma_bind_addr (struct rdma_cm_id*,struct sockaddr*) ; 

__attribute__((used)) static int cma_bind_addr(struct rdma_cm_id *id, struct sockaddr *src_addr,
			 struct sockaddr *dst_addr)
{
	if (!src_addr || !src_addr->sa_family) {
		src_addr = (struct sockaddr *) &id->route.addr.src_addr;
		src_addr->sa_family = dst_addr->sa_family;
		if (dst_addr->sa_family == AF_INET6) {
			((struct sockaddr_in6 *) src_addr)->sin6_scope_id =
				((struct sockaddr_in6 *) dst_addr)->sin6_scope_id;
		} else if (dst_addr->sa_family == AF_IB) {
			((struct sockaddr_ib *) src_addr)->sib_pkey =
				((struct sockaddr_ib *) dst_addr)->sib_pkey;
		}
	}
	return rdma_bind_addr(id, src_addr);
}