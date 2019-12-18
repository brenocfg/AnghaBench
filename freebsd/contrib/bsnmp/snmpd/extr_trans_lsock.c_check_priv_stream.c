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
typedef  int /*<<< orphan*/  ucred ;
struct xucred {scalar_t__ cr_version; scalar_t__ cr_uid; } ;
struct port_input {int priv; int /*<<< orphan*/  fd; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCAL_PEERCRED ; 
 scalar_t__ XUCRED_VERSION ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xucred*,int*) ; 

__attribute__((used)) static void
check_priv_stream(struct port_input *pi)
{
	struct xucred ucred;
	socklen_t ucredlen;

	/* obtain the accept time credentials */
	ucredlen = sizeof(ucred);

	if (getsockopt(pi->fd, 0, LOCAL_PEERCRED, &ucred, &ucredlen) == 0 &&
	    ucredlen >= sizeof(ucred) && ucred.cr_version == XUCRED_VERSION)
		pi->priv = (ucred.cr_uid == 0);
	else
		pi->priv = 0;
}