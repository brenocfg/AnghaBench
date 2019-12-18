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
typedef  int /*<<< orphan*/  user_siginfo_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  user64_siginfo_t ;
typedef  int /*<<< orphan*/  user32_siginfo_t ;
typedef  int /*<<< orphan*/  sinfo64 ;
typedef  int /*<<< orphan*/  sinfo32 ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siginfo_user_to_user32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  siginfo_user_to_user64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
copyoutsiginfo(user_siginfo_t *native, boolean_t is64, user_addr_t uaddr)
{
	if (is64) {
		user64_siginfo_t sinfo64;

		bzero(&sinfo64, sizeof (sinfo64));
		siginfo_user_to_user64(native, &sinfo64);
		return (copyout(&sinfo64, uaddr, sizeof (sinfo64)));
	} else {
		user32_siginfo_t sinfo32;

		bzero(&sinfo32, sizeof (sinfo32));
		siginfo_user_to_user32(native, &sinfo32);
		return (copyout(&sinfo32, uaddr, sizeof (sinfo32)));
	}
}