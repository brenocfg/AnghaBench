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
struct net_bridge {int /*<<< orphan*/  root_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  br_get_port (struct net_bridge*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_send_tcn_bpdu (int /*<<< orphan*/ ) ; 

void br_transmit_tcn(struct net_bridge *br)
{
	br_send_tcn_bpdu(br_get_port(br, br->root_port));
}