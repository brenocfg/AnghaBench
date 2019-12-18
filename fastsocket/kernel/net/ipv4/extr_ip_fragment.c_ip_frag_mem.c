#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mem; } ;
struct TYPE_4__ {TYPE_1__ frags; } ;
struct net {TYPE_2__ ipv4; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 

int ip_frag_mem(struct net *net)
{
	return atomic_read(&net->ipv4.frags.mem);
}