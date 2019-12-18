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
struct TYPE_2__ {int /*<<< orphan*/  fib6_main_tbl; } ;
struct net {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_link_table (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fib6_tables_init(struct net *net)
{
	fib6_link_table(net, net->ipv6.fib6_main_tbl);
}