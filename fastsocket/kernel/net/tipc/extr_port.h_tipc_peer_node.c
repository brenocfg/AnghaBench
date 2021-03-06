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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  phdr; } ;
struct port {TYPE_1__ publ; } ;

/* Variables and functions */
 int /*<<< orphan*/  msg_destnode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 tipc_peer_node(struct port *p_ptr)
{
	return msg_destnode(&p_ptr->publ.phdr);
}