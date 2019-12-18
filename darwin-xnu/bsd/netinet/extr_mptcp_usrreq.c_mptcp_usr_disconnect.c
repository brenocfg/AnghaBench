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

/* Variables and functions */
 int /*<<< orphan*/  mpsotompte (struct socket*) ; 
 int mptcp_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mptcp_usr_disconnect(struct socket *mp_so)
{
	return (mptcp_disconnect(mpsotompte(mp_so)));
}