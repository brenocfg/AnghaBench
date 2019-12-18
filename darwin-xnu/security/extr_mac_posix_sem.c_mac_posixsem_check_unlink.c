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
struct pseminfo {int /*<<< orphan*/  psem_label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pseminfo*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mac_posixsem_enforce ; 
 int /*<<< orphan*/  posixsem_check_unlink ; 

int
mac_posixsem_check_unlink(kauth_cred_t cred, struct pseminfo *psem,
    const char *name)
{
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
    /* 21167099 - only check if we allow write */
    if (!mac_posixsem_enforce)
        return (0);
#endif

	MAC_CHECK(posixsem_check_unlink, cred, psem, psem->psem_label, name);

	return (error);
}