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
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  vnode_isvroot (struct vnode*) ; 

__attribute__((used)) static boolean_t
devfs_is_name_protected(struct vnode *dvp, const char *name)
{
    /*
     * Only names in root are protected. E.g. /dev/null is protected,
     * but /dev/foo/null isn't.
     */
    if (!vnode_isvroot(dvp))
        return FALSE;

    if ((strcmp("console", name) == 0) ||
        (strcmp("tty", name) == 0) ||
        (strcmp("null", name) == 0) ||
        (strcmp("zero", name) == 0) ||
        (strcmp("klog", name) == 0)) {

        return TRUE;
    }

    return FALSE;
}