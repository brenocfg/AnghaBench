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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ addr_type; scalar_t__ pan_id; scalar_t__ short_addr; int /*<<< orphan*/  hwaddr; } ;
struct dgram_sock {TYPE_1__ src_addr; int /*<<< orphan*/  bound; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_ADDR_LEN ; 
 scalar_t__ IEEE802154_ADDR_LONG ; 
 scalar_t__ IEEE802154_ADDR_SHORT ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ieee802154_match_sock(u8 *hw_addr, u16 pan_id,
		u16 short_addr, struct dgram_sock *ro)
{
	if (!ro->bound)
		return 1;

	if (ro->src_addr.addr_type == IEEE802154_ADDR_LONG &&
	    !memcmp(ro->src_addr.hwaddr, hw_addr, IEEE802154_ADDR_LEN))
		return 1;

	if (ro->src_addr.addr_type == IEEE802154_ADDR_SHORT &&
		     pan_id == ro->src_addr.pan_id &&
		     short_addr == ro->src_addr.short_addr)
		return 1;

	return 0;
}