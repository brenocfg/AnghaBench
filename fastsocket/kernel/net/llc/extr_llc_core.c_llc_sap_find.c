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
struct llc_sap {int dummy; } ;

/* Variables and functions */
 struct llc_sap* __llc_sap_find (unsigned char) ; 
 int /*<<< orphan*/  llc_sap_hold (struct llc_sap*) ; 
 int /*<<< orphan*/  llc_sap_list_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

struct llc_sap *llc_sap_find(unsigned char sap_value)
{
	struct llc_sap* sap;

	read_lock_bh(&llc_sap_list_lock);
	sap = __llc_sap_find(sap_value);
	if (sap)
		llc_sap_hold(sap);
	read_unlock_bh(&llc_sap_list_lock);
	return sap;
}