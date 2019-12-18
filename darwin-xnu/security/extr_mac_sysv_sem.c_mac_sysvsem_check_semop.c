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
struct semid_kernel {int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct semid_kernel*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mac_sysvsem_enforce ; 
 int /*<<< orphan*/  sysvsem_check_semop ; 

int
mac_sysvsem_check_semop(kauth_cred_t cred, struct semid_kernel *semakptr,
    size_t accesstype)
{
	int error;

#if SECURITY_MAC_CHECK_ENFORCE
    /* 21167099 - only check if we allow write */
    if (!mac_sysvsem_enforce)
        return (0);
#endif

	MAC_CHECK(sysvsem_check_semop, cred, semakptr, semakptr->label,
	    accesstype);

	return(error);
}