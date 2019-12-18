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
struct ucred {int dummy; } ;
struct shmid_kernel {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct ucred*,struct shmid_kernel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_sysvshm_enforce ; 
 int /*<<< orphan*/  sysvshm_check_shmdt ; 

int
mac_sysvshm_check_shmdt(struct ucred *cred, struct shmid_kernel *shmsegptr)
{
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
    /* 21167099 - only check if we allow write */
    if (!mac_sysvshm_enforce)
        return (0);
#endif

	MAC_CHECK(sysvshm_check_shmdt, cred, shmsegptr, shmsegptr->label);

	return(error);
}