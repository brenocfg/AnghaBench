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
struct vnop_pathconf_args {int a_name; int* a_retval; } ;

/* Variables and functions */
 int EINVAL ; 
 int LINK_MAX ; 
 int PIPE_BUF ; 
#define  _PC_CHOWN_RESTRICTED 130 
#define  _PC_LINK_MAX 129 
#define  _PC_PIPE_BUF 128 

int
fifo_pathconf(struct vnop_pathconf_args *ap)
{
	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 200112;		/* _POSIX_CHOWN_RESTRICTED */
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
}