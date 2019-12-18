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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct ip_set {char* name; int /*<<< orphan*/  ref; TYPE_1__* type; } ;
typedef  size_t ip_set_id_t ;
struct TYPE_2__ {scalar_t__ features; scalar_t__ family; } ;

/* Variables and functions */
 int ENOENT ; 
 size_t IPSET_ATTR_SETNAME ; 
 size_t IPSET_ATTR_SETNAME2 ; 
 int IPSET_ERR_EXIST_SETNAME2 ; 
 int IPSET_ERR_PROTOCOL ; 
 int IPSET_ERR_TYPE_MISMATCH ; 
 size_t IPSET_INVALID_ID ; 
 int IPSET_MAXNAMELEN ; 
 size_t find_set_id (int /*<<< orphan*/ ) ; 
 struct ip_set** ip_set_list ; 
 int /*<<< orphan*/  ip_set_ref_lock ; 
 int /*<<< orphan*/  nla_data (struct nlattr const* const) ; 
 scalar_t__ protocol_failed (struct nlattr const* const*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ip_set_swap(struct sock *ctnl, struct sk_buff *skb,
	    const struct nlmsghdr *nlh,
	    const struct nlattr * const attr[])
{
	struct ip_set *from, *to;
	ip_set_id_t from_id, to_id;
	char from_name[IPSET_MAXNAMELEN];

	if (unlikely(protocol_failed(attr) ||
		     attr[IPSET_ATTR_SETNAME] == NULL ||
		     attr[IPSET_ATTR_SETNAME2] == NULL))
		return -IPSET_ERR_PROTOCOL;

	from_id = find_set_id(nla_data(attr[IPSET_ATTR_SETNAME]));
	if (from_id == IPSET_INVALID_ID)
		return -ENOENT;

	to_id = find_set_id(nla_data(attr[IPSET_ATTR_SETNAME2]));
	if (to_id == IPSET_INVALID_ID)
		return -IPSET_ERR_EXIST_SETNAME2;

	from = ip_set_list[from_id];
	to = ip_set_list[to_id];

	/* Features must not change.
	 * Not an artificial restriction anymore, as we must prevent
	 * possible loops created by swapping in setlist type of sets. */
	if (!(from->type->features == to->type->features &&
	      from->type->family == to->type->family))
		return -IPSET_ERR_TYPE_MISMATCH;

	strncpy(from_name, from->name, IPSET_MAXNAMELEN);
	strncpy(from->name, to->name, IPSET_MAXNAMELEN);
	strncpy(to->name, from_name, IPSET_MAXNAMELEN);

	write_lock_bh(&ip_set_ref_lock);
	swap(from->ref, to->ref);
	ip_set_list[from_id] = to;
	ip_set_list[to_id] = from;
	write_unlock_bh(&ip_set_ref_lock);

	return 0;
}