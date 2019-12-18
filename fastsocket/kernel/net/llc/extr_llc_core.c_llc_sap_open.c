#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char lsap; } ;
struct llc_sap {int (* rcv_func ) (struct sk_buff*,struct net_device*,struct packet_type*,struct net_device*) ;TYPE_1__ laddr; } ;

/* Variables and functions */
 scalar_t__ __llc_sap_find (unsigned char) ; 
 int /*<<< orphan*/  llc_add_sap (struct llc_sap*) ; 
 struct llc_sap* llc_sap_alloc () ; 
 int /*<<< orphan*/  llc_sap_list_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct llc_sap *llc_sap_open(unsigned char lsap,
			     int (*func)(struct sk_buff *skb,
					 struct net_device *dev,
					 struct packet_type *pt,
					 struct net_device *orig_dev))
{
	struct llc_sap *sap = NULL;

	write_lock_bh(&llc_sap_list_lock);
	if (__llc_sap_find(lsap)) /* SAP already exists */
		goto out;
	sap = llc_sap_alloc();
	if (!sap)
		goto out;
	sap->laddr.lsap = lsap;
	sap->rcv_func	= func;
	llc_add_sap(sap);
out:
	write_unlock_bh(&llc_sap_list_lock);
	return sap;
}