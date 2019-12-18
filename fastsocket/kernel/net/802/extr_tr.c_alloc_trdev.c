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
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tr_setup ; 

struct net_device *alloc_trdev(int sizeof_priv)
{
	return alloc_netdev(sizeof_priv, "tr%d", tr_setup);
}