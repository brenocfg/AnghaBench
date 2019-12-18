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
typedef  int /*<<< orphan*/  xfrm_address_t ;
struct net {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl6_src; int /*<<< orphan*/  fl6_dst; } ;
struct dst_entry {int error; } ;

/* Variables and functions */
 struct dst_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 struct dst_entry* ip6_route_output (struct net*,int /*<<< orphan*/ *,struct flowi*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct dst_entry *xfrm6_dst_lookup(struct net *net, int tos,
					  xfrm_address_t *saddr,
					  xfrm_address_t *daddr)
{
	struct flowi fl = {};
	struct dst_entry *dst;
	int err;

	memcpy(&fl.fl6_dst, daddr, sizeof(fl.fl6_dst));
	if (saddr)
		memcpy(&fl.fl6_src, saddr, sizeof(fl.fl6_src));

	dst = ip6_route_output(net, NULL, &fl);

	err = dst->error;
	if (dst->error) {
		dst_release(dst);
		dst = ERR_PTR(err);
	}

	return dst;
}