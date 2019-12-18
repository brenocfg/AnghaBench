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
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  domid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GTF_accept_transfer ; 
 int /*<<< orphan*/  update_grant_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

void gnttab_grant_foreign_transfer_ref(grant_ref_t ref, domid_t domid,
				       unsigned long pfn)
{
	update_grant_entry(ref, domid, pfn, GTF_accept_transfer);
}