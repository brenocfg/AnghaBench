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
struct socket {int dummy; } ;
typedef  int /*<<< orphan*/  sae_connid_t ;
typedef  int /*<<< orphan*/  sae_associd_t ;

/* Variables and functions */
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 
 int sodisconnectxlocked (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sodisconnectx(struct socket *so, sae_associd_t aid, sae_connid_t cid)
{
	int error;

	socket_lock(so, 1);
	error = sodisconnectxlocked(so, aid, cid);
	socket_unlock(so, 1);
	return (error);
}