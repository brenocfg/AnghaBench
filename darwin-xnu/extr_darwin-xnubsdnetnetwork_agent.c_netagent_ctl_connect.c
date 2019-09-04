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
struct sockaddr_ctl {int /*<<< orphan*/  sc_unit; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 void* netagent_create_session (int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
netagent_ctl_connect(kern_ctl_ref kctlref, struct sockaddr_ctl *sac, void **unitinfo)
{
#pragma unused(kctlref)
	*unitinfo = netagent_create_session(sac->sc_unit);
	if (*unitinfo == NULL) {
		// Could not allocate session
		return (ENOBUFS);
	}

	return (0);
}