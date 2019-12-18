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
struct hh_cache {scalar_t__ hh_type; int hh_len; scalar_t__ hh_data; } ;
struct eth1394hdr {int /*<<< orphan*/  h_dest; scalar_t__ h_proto; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int ETH1394_HLEN ; 
 int /*<<< orphan*/  ETH_P_802_3 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ether1394_header_cache(const struct neighbour *neigh,
				  struct hh_cache *hh)
{
	__be16 type = hh->hh_type;
	struct net_device *dev = neigh->dev;
	struct eth1394hdr *eth =
		(struct eth1394hdr *)((u8 *)hh->hh_data + 16 - ETH1394_HLEN);

	if (type == htons(ETH_P_802_3))
		return -1;

	eth->h_proto = type;
	memcpy(eth->h_dest, neigh->ha, dev->addr_len);

	hh->hh_len = ETH1394_HLEN;
	return 0;
}