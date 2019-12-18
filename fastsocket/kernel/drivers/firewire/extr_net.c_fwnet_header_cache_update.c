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
struct hh_cache {scalar_t__ hh_data; } ;

/* Variables and functions */
 int FWNET_HLEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fwnet_header_cache_update(struct hh_cache *hh,
		const struct net_device *net, const unsigned char *haddr)
{
	memcpy((u8 *)hh->hh_data + 16 - FWNET_HLEN, haddr, net->addr_len);
}