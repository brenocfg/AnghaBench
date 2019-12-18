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
struct o2net_sock_container {int dummy; } ;
struct o2net_node {int /*<<< orphan*/  nn_lock; struct o2net_sock_container* nn_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  o2net_set_nn_state (struct o2net_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_ensure_shutdown(struct o2net_node *nn,
			           struct o2net_sock_container *sc,
				   int err)
{
	spin_lock(&nn->nn_lock);
	if (nn->nn_sc == sc)
		o2net_set_nn_state(nn, NULL, 0, err);
	spin_unlock(&nn->nn_lock);
}