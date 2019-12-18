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
struct net_bridge_port {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_stp_set_path_cost (struct net_bridge_port*,unsigned long) ; 

__attribute__((used)) static ssize_t store_path_cost(struct net_bridge_port *p, unsigned long v)
{
	br_stp_set_path_cost(p, v);
	return 0;
}