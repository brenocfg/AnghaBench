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
struct socket_args {int /*<<< orphan*/  protocol; int /*<<< orphan*/  type; int /*<<< orphan*/  domain; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_selfpid () ; 
 int socket_common (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
socket(struct proc *p,
	struct socket_args *uap,
	int32_t *retval)
{
	return (socket_common(p, uap->domain, uap->type, uap->protocol,
	    proc_selfpid(), retval, 0));
}