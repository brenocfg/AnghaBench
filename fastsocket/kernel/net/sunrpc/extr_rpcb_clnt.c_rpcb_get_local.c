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

/* Variables and functions */
 int /*<<< orphan*/  rpcb_clnt_lock ; 
 int rpcb_users ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpcb_get_local(void)
{
	int cnt;

	spin_lock(&rpcb_clnt_lock);
	if (rpcb_users)
		rpcb_users++;
	cnt = rpcb_users;
	spin_unlock(&rpcb_clnt_lock);

	return cnt;
}