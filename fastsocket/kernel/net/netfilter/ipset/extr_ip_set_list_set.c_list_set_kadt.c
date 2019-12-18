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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct set_elem {scalar_t__ id; } ;
struct list_set {scalar_t__ size; int /*<<< orphan*/  timeout; } ;
struct ip_set {struct list_set* data; } ;
typedef  enum ipset_adt { ____Placeholder_ipset_adt } ipset_adt ;

/* Variables and functions */
 int EINVAL ; 
#define  IPSET_ADD 130 
#define  IPSET_DEL 129 
 scalar_t__ IPSET_INVALID_ID ; 
#define  IPSET_TEST 128 
 int ip_set_add (scalar_t__,struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ip_set_del (scalar_t__,struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ip_set_test (scalar_t__,struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct set_elem* list_set_elem (struct list_set*,scalar_t__) ; 
 scalar_t__ list_set_expired (struct list_set*,scalar_t__) ; 
 scalar_t__ with_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
list_set_kadt(struct ip_set *set, const struct sk_buff *skb,
	      enum ipset_adt adt, u8 pf, u8 dim, u8 flags)
{
	struct list_set *map = set->data;
	struct set_elem *elem;
	u32 i;
	int ret;

	for (i = 0; i < map->size; i++) {
		elem = list_set_elem(map, i);
		if (elem->id == IPSET_INVALID_ID)
			return 0;
		if (with_timeout(map->timeout) && list_set_expired(map, i))
			continue;
		switch (adt) {
		case IPSET_TEST:
			ret = ip_set_test(elem->id, skb, pf, dim, flags);
			if (ret > 0)
				return ret;
			break;
		case IPSET_ADD:
			ret = ip_set_add(elem->id, skb, pf, dim, flags);
			if (ret == 0)
				return ret;
			break;
		case IPSET_DEL:
			ret = ip_set_del(elem->id, skb, pf, dim, flags);
			if (ret == 0)
				return ret;
			break;
		default:
			break;
		}
	}
	return -EINVAL;
}