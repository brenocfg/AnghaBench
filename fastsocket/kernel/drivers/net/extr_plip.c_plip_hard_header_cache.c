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
struct neighbour {int /*<<< orphan*/  dev; } ;
struct hh_cache {scalar_t__ hh_data; } ;
struct ethhdr {int dummy; } ;

/* Variables and functions */
 int HH_DATA_OFF (int) ; 
 int eth_header_cache (struct neighbour const*,struct hh_cache*) ; 
 int /*<<< orphan*/  plip_rewrite_address (int /*<<< orphan*/ ,struct ethhdr*) ; 

__attribute__((used)) static int plip_hard_header_cache(const struct neighbour *neigh,
				  struct hh_cache *hh)
{
	int ret;

	ret = eth_header_cache(neigh, hh);
	if (ret == 0) {
		struct ethhdr *eth;

		eth = (struct ethhdr*)(((u8*)hh->hh_data) +
				       HH_DATA_OFF(sizeof(*eth)));
		plip_rewrite_address (neigh->dev, eth);
	}

	return ret;
}