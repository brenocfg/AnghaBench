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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_portid {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_PORT_IMPORTANCE ; 
 int tipc_forward_buf2port (int /*<<< orphan*/ ,struct tipc_portid const*,struct sk_buff*,unsigned int,struct tipc_portid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr ; 

int tipc_send_buf2port(u32 ref,
		       struct tipc_portid const *dest,
		       struct sk_buff *buf,
		       unsigned int dsz)
{
	struct tipc_portid orig;

	orig.ref = ref;
	orig.node = tipc_own_addr;
	return tipc_forward_buf2port(ref, dest, buf, dsz, &orig,
				     TIPC_PORT_IMPORTANCE);
}