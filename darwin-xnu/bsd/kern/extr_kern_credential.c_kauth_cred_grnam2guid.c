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
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KI_VALID_GRNAM ; 
 int /*<<< orphan*/  KI_VALID_GUID ; 
 int kauth_cred_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int
kauth_cred_grnam2guid(char *grnam, guid_t *guidp)
{
	return(kauth_cred_cache_lookup(KI_VALID_GRNAM, KI_VALID_GUID, grnam, guidp));
}