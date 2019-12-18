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
struct net_protocol {int dummy; } ;

/* Variables and functions */
 int MAX_INET_PROTOS ; 
 int /*<<< orphan*/  inet_proto_lock ; 
 struct net_protocol const** inet_protos ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int inet_add_protocol(const struct net_protocol *prot, unsigned char protocol)
{
	int hash, ret;

	hash = protocol & (MAX_INET_PROTOS - 1);

	spin_lock_bh(&inet_proto_lock);
	if (inet_protos[hash]) {
		ret = -1;
	} else {
		inet_protos[hash] = prot;
		ret = 0;
	}
	spin_unlock_bh(&inet_proto_lock);

	return ret;
}