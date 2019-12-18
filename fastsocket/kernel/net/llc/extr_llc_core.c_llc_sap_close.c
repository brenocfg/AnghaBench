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
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct llc_sap {TYPE_1__ sk_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct llc_sap*) ; 
 int /*<<< orphan*/  llc_del_sap (struct llc_sap*) ; 

void llc_sap_close(struct llc_sap *sap)
{
	WARN_ON(!hlist_empty(&sap->sk_list.list));
	llc_del_sap(sap);
	kfree(sap);
}