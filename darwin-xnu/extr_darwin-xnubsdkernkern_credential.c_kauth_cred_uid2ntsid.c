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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  ntsid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KI_VALID_NTSID ; 
 int /*<<< orphan*/  KI_VALID_UID ; 
 int kauth_cred_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
kauth_cred_uid2ntsid(uid_t uid, ntsid_t *sidp)
{
	return(kauth_cred_cache_lookup(KI_VALID_UID, KI_VALID_NTSID, &uid, sidp));
}