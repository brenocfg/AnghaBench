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
struct netfs_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netfs_state_exit (struct netfs_state*) ; 
 int /*<<< orphan*/  netfs_state_init (struct netfs_state*) ; 
 int /*<<< orphan*/  netfs_state_lock_send (struct netfs_state*) ; 
 int /*<<< orphan*/  netfs_state_unlock_send (struct netfs_state*) ; 

__attribute__((used)) static void __inline__ netfs_state_reset(struct netfs_state *st)
{
	netfs_state_lock_send(st);
	netfs_state_exit(st);
	netfs_state_init(st);
	netfs_state_unlock_send(st);
}