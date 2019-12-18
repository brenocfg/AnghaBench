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
struct sockaddr_ctl {int dummy; } ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */

__attribute__((used)) static errno_t
netsrc_ctlconnect(kern_ctl_ref kctl, struct sockaddr_ctl *sac, void **uinfo)
{
#pragma unused(kctl, sac, uinfo)

	/*
	 * We don't need to do anything here. This callback is only necessary
	 * for ctl_register() to succeed.
	 */
	return (0);
}