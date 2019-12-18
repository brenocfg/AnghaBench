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
typedef  int /*<<< orphan*/  udp_recv_fn ;
struct udp_pcb {int dummy; } ;

/* Variables and functions */

void udp_recv(struct udp_pcb *pcb, udp_recv_fn recv, void *recv_arg)
{
}