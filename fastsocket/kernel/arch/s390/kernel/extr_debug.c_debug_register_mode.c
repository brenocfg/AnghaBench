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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  debug_flush_view ; 
 int /*<<< orphan*/ * debug_info_create (char const*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_level_view ; 
 int /*<<< orphan*/  debug_mutex ; 
 int /*<<< orphan*/  debug_pages_view ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialized ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

debug_info_t *debug_register_mode(const char *name, int pages_per_area,
				  int nr_areas, int buf_size, mode_t mode,
				  uid_t uid, gid_t gid)
{
	debug_info_t *rc = NULL;

	/* Since debugfs currently does not support uid/gid other than root, */
	/* we do not allow gid/uid != 0 until we get support for that. */
	if ((uid != 0) || (gid != 0))
		pr_warning("Root becomes the owner of all s390dbf files "
			   "in sysfs\n");
	BUG_ON(!initialized);
	mutex_lock(&debug_mutex);

        /* create new debug_info */

	rc = debug_info_create(name, pages_per_area, nr_areas, buf_size, mode);
	if(!rc) 
		goto out;
	debug_register_view(rc, &debug_level_view);
        debug_register_view(rc, &debug_flush_view);
	debug_register_view(rc, &debug_pages_view);
out:
        if (!rc){
		pr_err("Registering debug feature %s failed\n", name);
        }
	mutex_unlock(&debug_mutex);
	return rc;
}