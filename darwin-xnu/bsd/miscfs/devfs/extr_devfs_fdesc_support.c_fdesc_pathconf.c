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
 int MAX_CANON ; 
 int MAX_INPUT ; 
 int PIPE_BUF ; 
#define  _PC_CHOWN_RESTRICTED 133 
#define  _PC_LINK_MAX 132 
#define  _PC_MAX_CANON 131 
#define  _PC_MAX_INPUT 130 
#define  _PC_PIPE_BUF 129 
#define  _PC_VDISABLE 128 
 int _POSIX_VDISABLE ; 

int
fdesc_pathconf(struct vnop_pathconf_args *ap)
{

	switch (ap->a_name) {
	case _PC_LINK_MAX:
		*ap->a_retval = LINK_MAX;
		return (0);
	case _PC_MAX_CANON:
		*ap->a_retval = MAX_CANON;
		return (0);
	case _PC_MAX_INPUT:
		*ap->a_retval = MAX_INPUT;
		return (0);
	case _PC_PIPE_BUF:
		*ap->a_retval = PIPE_BUF;
		return (0);
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 200112;		/* _POSIX_CHOWN_RESTRICTED */
		return (0);
	case _PC_VDISABLE:
		*ap->a_retval = _POSIX_VDISABLE;
		return (0);
	default:
		return (EINVAL);
	}
	/* NOTREACHED */
}