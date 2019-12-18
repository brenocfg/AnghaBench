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
struct TYPE_2__ {int /*<<< orphan*/  policycaps; } ;

/* Variables and functions */
 int ebitmap_get_bit (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  policy_rwlock ; 
 TYPE_1__ policydb ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int security_policycap_supported(unsigned int req_cap)
{
	int rc;

	read_lock(&policy_rwlock);
	rc = ebitmap_get_bit(&policydb.policycaps, req_cap);
	read_unlock(&policy_rwlock);

	return rc;
}