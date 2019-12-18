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
struct ethhdr {scalar_t__ h_proto; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int VLAN_ETH_HLEN ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int eth_hdr_len(const void *data)
{
	const struct ethhdr *e = data;

	return e->h_proto == htons(ETH_P_8021Q) ? VLAN_ETH_HLEN : ETH_HLEN;
}