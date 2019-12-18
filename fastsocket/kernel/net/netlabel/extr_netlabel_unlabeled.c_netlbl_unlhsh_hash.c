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
typedef  int u32 ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlbl_unlhsh ; 
 TYPE_1__* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 netlbl_unlhsh_hash(int ifindex)
{
	/* this is taken _almost_ directly from
	 * security/selinux/netif.c:sel_netif_hasfn() as they do pretty much
	 * the same thing */
	return ifindex & (rcu_dereference(netlbl_unlhsh)->size - 1);
}