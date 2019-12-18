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
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rpcb_create_local_net () ; 
 scalar_t__ rpcb_create_local_unix () ; 
 scalar_t__ rpcb_get_local () ; 

int rpcb_create_local(void)
{
	static DEFINE_MUTEX(rpcb_create_local_mutex);
	int result = 0;

	if (rpcb_get_local())
		return result;

	mutex_lock(&rpcb_create_local_mutex);
	if (rpcb_get_local())
		goto out;

	if (rpcb_create_local_unix() != 0)
		result = rpcb_create_local_net();

out:
	mutex_unlock(&rpcb_create_local_mutex);
	return result;
}