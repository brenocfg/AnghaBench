#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sk_buff {struct sk_buff* next; } ;
struct TYPE_3__ {struct sk_buff* first_out; } ;

/* Variables and functions */
 TYPE_1__* bcl ; 
 int /*<<< orphan*/  buf_seqno (struct sk_buff*) ; 
 scalar_t__ less_eq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mod (scalar_t__) ; 
 int /*<<< orphan*/  tipc_link_retransmit (TYPE_1__*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bclink_retransmit_pkt(u32 after, u32 to)
{
	struct sk_buff *buf;

	buf = bcl->first_out;
	while (buf && less_eq(buf_seqno(buf), after)) {
		buf = buf->next;
	}
	tipc_link_retransmit(bcl, buf, mod(to - after));
}