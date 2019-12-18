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
 int /*<<< orphan*/  DEVMAXNAMESIZE ; 
 int /*<<< orphan*/  DEVMAXPATHSIZE ; 
 int EINVAL ; 
#define  _PC_CASE_PRESERVING 134 
#define  _PC_CASE_SENSITIVE 133 
#define  _PC_CHOWN_RESTRICTED 132 
#define  _PC_LINK_MAX 131 
#define  _PC_NAME_MAX 130 
#define  _PC_NO_TRUNC 129 
#define  _PC_PATH_MAX 128 

__attribute__((used)) static int
devs_vnop_pathconf(
	struct vnop_pathconf_args /* {
		struct vnode *a_vp;
		int a_name;
		int *a_retval;
		vfs_context_t a_context;
	} */ *ap)
{
	switch (ap->a_name) {
	case _PC_LINK_MAX:
		/* arbitrary limit matching HFS; devfs has no hard limit */
		*ap->a_retval = 32767;
		break;
	case _PC_NAME_MAX:
		*ap->a_retval = DEVMAXNAMESIZE - 1;	/* includes NUL */
		break;
	case _PC_PATH_MAX:
		*ap->a_retval = DEVMAXPATHSIZE - 1;	/* XXX nonconformant */
		break;
	case _PC_CHOWN_RESTRICTED:
		*ap->a_retval = 200112;		/* _POSIX_CHOWN_RESTRICTED */
		break;
	case _PC_NO_TRUNC:
		*ap->a_retval = 0;
		break;
	case _PC_CASE_SENSITIVE:
		*ap->a_retval = 1;
		break;
	case _PC_CASE_PRESERVING:
		*ap->a_retval = 1;
		break;
	default:
		return (EINVAL);
	}

	return (0);
}