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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASU ; 
 int EPERM ; 
 int /*<<< orphan*/  IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
suser(kauth_cred_t cred, u_short *acflag)
{
#if DIAGNOSTIC
	if (!IS_VALID_CRED(cred))
		panic("suser");
#endif
	if (kauth_cred_getuid(cred) == 0) {
		if (acflag)
			*acflag |= ASU;
		return (0);
	}
	return (EPERM);
}