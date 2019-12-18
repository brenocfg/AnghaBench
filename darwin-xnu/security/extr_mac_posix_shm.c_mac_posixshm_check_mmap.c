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
struct pshminfo {int /*<<< orphan*/  pshm_label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pshminfo*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mac_posixshm_enforce ; 
 int /*<<< orphan*/  posixshm_check_mmap ; 

int
mac_posixshm_check_mmap(kauth_cred_t cred, struct pshminfo *shm,
    int prot, int flags)
{
	int error = 0;

#if SECURITY_MAC_CHECK_ENFORCE
    /* 21167099 - only check if we allow write */
    if (!mac_posixshm_enforce)
        return 0;
#endif

	MAC_CHECK(posixshm_check_mmap, cred, shm, shm->pshm_label,
            prot, flags);

	return (error);
}