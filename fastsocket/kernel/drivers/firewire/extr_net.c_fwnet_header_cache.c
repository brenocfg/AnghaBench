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
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct neighbour {int /*<<< orphan*/  ha; struct net_device* dev; } ;
struct hh_cache {scalar_t__ hh_type; int /*<<< orphan*/  hh_len; scalar_t__ hh_data; } ;
struct fwnet_header {scalar_t__ h_proto; int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_802_3 ; 
 int /*<<< orphan*/  FWNET_HLEN ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fwnet_header_cache(const struct neighbour *neigh,
			      struct hh_cache *hh)
{
	struct net_device *net;
	struct fwnet_header *h;

	if (hh->hh_type == cpu_to_be16(ETH_P_802_3))
		return -1;
	net = neigh->dev;
	h = (struct fwnet_header *)((u8 *)hh->hh_data + 16 - sizeof(*h));
	h->h_proto = hh->hh_type;
	memcpy(h->h_dest, neigh->ha, net->addr_len);
	hh->hh_len = FWNET_HLEN;

	return 0;
}