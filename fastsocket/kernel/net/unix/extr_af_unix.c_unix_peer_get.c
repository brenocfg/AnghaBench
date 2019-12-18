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
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 struct sock* unix_peer (struct sock*) ; 
 int /*<<< orphan*/  unix_state_lock (struct sock*) ; 
 int /*<<< orphan*/  unix_state_unlock (struct sock*) ; 

__attribute__((used)) static struct sock *unix_peer_get(struct sock *s)
{
	struct sock *peer;

	unix_state_lock(s);
	peer = unix_peer(s);
	if (peer)
		sock_hold(peer);
	unix_state_unlock(s);
	return peer;
}