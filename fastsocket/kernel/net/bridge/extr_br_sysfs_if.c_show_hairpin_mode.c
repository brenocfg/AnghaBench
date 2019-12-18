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
struct net_bridge_port {int flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int BR_HAIRPIN_MODE ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_hairpin_mode(struct net_bridge_port *p, char *buf)
{
	int hairpin_mode = (p->flags & BR_HAIRPIN_MODE) ? 1 : 0;
	return sprintf(buf, "%d\n", hairpin_mode);
}