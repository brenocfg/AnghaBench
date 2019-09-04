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
typedef  size_t u_int32_t ;
struct ifnet {int /*<<< orphan*/ * if_proto_hash; } ;
struct if_proto {size_t protocol_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_LCK_ASSERT_OWNED ; 
 struct if_proto* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct if_proto* SLIST_NEXT (struct if_proto*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_proto_ref (struct if_proto*) ; 
 int /*<<< orphan*/  ifnet_lock_assert (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_hash ; 
 size_t proto_hash_value (size_t) ; 

__attribute__((used)) static struct if_proto *
find_attached_proto(struct ifnet *ifp, u_int32_t protocol_family)
{
	struct if_proto *proto = NULL;
	u_int32_t i = proto_hash_value(protocol_family);

	ifnet_lock_assert(ifp, IFNET_LCK_ASSERT_OWNED);

	if (ifp->if_proto_hash != NULL)
		proto = SLIST_FIRST(&ifp->if_proto_hash[i]);

	while (proto != NULL && proto->protocol_family != protocol_family)
		proto = SLIST_NEXT(proto, next_hash);

	if (proto != NULL)
		if_proto_ref(proto);

	return (proto);
}