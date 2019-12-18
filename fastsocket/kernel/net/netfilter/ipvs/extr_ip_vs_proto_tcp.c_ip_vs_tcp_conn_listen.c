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
struct ip_vs_conn {size_t state; int /*<<< orphan*/  lock; int /*<<< orphan*/  timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/ * timeout_table; } ;

/* Variables and functions */
 size_t IP_VS_TCP_S_LISTEN ; 
 TYPE_1__ ip_vs_protocol_tcp ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ip_vs_tcp_conn_listen(struct ip_vs_conn *cp)
{
	spin_lock(&cp->lock);
	cp->state = IP_VS_TCP_S_LISTEN;
	cp->timeout = ip_vs_protocol_tcp.timeout_table[IP_VS_TCP_S_LISTEN];
	spin_unlock(&cp->lock);
}