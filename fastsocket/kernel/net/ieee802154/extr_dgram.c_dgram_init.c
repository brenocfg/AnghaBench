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
struct TYPE_2__ {int pan_id; int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  addr_type; } ;
struct dgram_sock {int want_ack; TYPE_1__ dst_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802154_ADDR_LONG ; 
 struct dgram_sock* dgram_sk (struct sock*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int dgram_init(struct sock *sk)
{
	struct dgram_sock *ro = dgram_sk(sk);

	ro->dst_addr.addr_type = IEEE802154_ADDR_LONG;
	ro->dst_addr.pan_id = 0xffff;
	ro->want_ack = 1;
	memset(&ro->dst_addr.hwaddr, 0xff, sizeof(ro->dst_addr.hwaddr));
	return 0;
}