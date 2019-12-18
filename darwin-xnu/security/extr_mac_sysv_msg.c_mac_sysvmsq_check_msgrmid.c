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
struct msg {int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_sysvmsg_enforce ; 
 int /*<<< orphan*/  sysvmsq_check_msgrmid ; 

int
mac_sysvmsq_check_msgrmid(kauth_cred_t cred, struct msg *msgptr)
{
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
    /* 21167099 - only check if we allow write */
    if (!mac_sysvmsg_enforce)
        return (0);
#endif

	MAC_CHECK(sysvmsq_check_msgrmid, cred,  msgptr, msgptr->label);

	return(error);
}