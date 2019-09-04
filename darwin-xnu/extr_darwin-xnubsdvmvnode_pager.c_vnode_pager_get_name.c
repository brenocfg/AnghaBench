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
typedef  scalar_t__ vm_size_t ;
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  safe_getpath (struct vnode*,int /*<<< orphan*/ *,char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 char* vnode_getname_printable (struct vnode*) ; 
 int /*<<< orphan*/  vnode_putname_printable (char const*) ; 

kern_return_t
vnode_pager_get_name(
	struct vnode	*vp,
	char		*pathname,
	vm_size_t	pathname_len,
	char 		*filename,
	vm_size_t	filename_len,
	boolean_t	*truncated_path_p)
{
	*truncated_path_p = FALSE;
	if (pathname != NULL) {
		/* get the path name */
		safe_getpath(vp, NULL,
			     pathname, (int) pathname_len,
			     truncated_path_p);
	}
	if ((pathname == NULL || *truncated_path_p) &&
	    filename != NULL) {
		/* get the file name */
		const char *name;

		name = vnode_getname_printable(vp);
		strlcpy(filename, name, (size_t) filename_len);
		vnode_putname_printable(name);
	}
	return KERN_SUCCESS;
}