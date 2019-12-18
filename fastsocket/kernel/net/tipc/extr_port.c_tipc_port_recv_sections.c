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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phdr; } ;
struct port {int /*<<< orphan*/  user_port; TYPE_1__ publ; } ;
struct iovec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MSG_SIZE ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int msg_build (int /*<<< orphan*/ *,struct iovec const*,unsigned int,int /*<<< orphan*/ ,int,struct sk_buff**) ; 
 int /*<<< orphan*/  tipc_port_recv_msg (struct sk_buff*) ; 

int tipc_port_recv_sections(struct port *sender, unsigned int num_sect,
		       struct iovec const *msg_sect)
{
	struct sk_buff *buf;
	int res;

	res = msg_build(&sender->publ.phdr, msg_sect, num_sect,
			MAX_MSG_SIZE, !sender->user_port, &buf);
	if (likely(buf))
		tipc_port_recv_msg(buf);
	return res;
}