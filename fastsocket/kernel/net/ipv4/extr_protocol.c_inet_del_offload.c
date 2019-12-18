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
struct net_offload {int dummy; } ;

/* Variables and functions */
 int MAX_INET_PROTOS ; 
 int /*<<< orphan*/  inet_offload_lock ; 
 struct net_offload const** inet_offloads ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 

int inet_del_offload(const struct net_offload *prot, unsigned char protocol)
{
	int hash, ret;

	hash = protocol & (MAX_INET_PROTOS - 1);

	spin_lock_bh(&inet_offload_lock);
	if (inet_offloads[hash] == prot) {
		inet_offloads[hash] = NULL;
		ret = 0;
	} else {
		ret = -1;
	}
	spin_unlock_bh(&inet_offload_lock);

	synchronize_net();

	return ret;
}