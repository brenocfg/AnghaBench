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
typedef  int /*<<< orphan*/  ntsid_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  NULLCRED_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int kauth_cred_uid2ntsid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
kauth_cred_getntsid(kauth_cred_t cred, ntsid_t *sidp)
{
	NULLCRED_CHECK(cred);
	return(kauth_cred_uid2ntsid(kauth_cred_getuid(cred), sidp));
}