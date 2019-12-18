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
struct elist_cb_state {int t; int n; unsigned char* ptr; unsigned char* rs; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dn_neigh_table ; 
 int /*<<< orphan*/  neigh_elist_cb ; 
 int /*<<< orphan*/  neigh_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct elist_cb_state*) ; 

int dn_neigh_elist(struct net_device *dev, unsigned char *ptr, int n)
{
	struct elist_cb_state state;

	state.dev = dev;
	state.t = 0;
	state.n = n;
	state.ptr = ptr;
	state.rs = ptr;

	neigh_for_each(&dn_neigh_table, neigh_elist_cb, &state);

	return state.t;
}