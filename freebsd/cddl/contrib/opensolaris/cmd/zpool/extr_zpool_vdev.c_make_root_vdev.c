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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  zpool_boot_label_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ check_replication (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * construct_spec (int,char**) ; 
 scalar_t__ is_device_in_use (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int is_force ; 
 scalar_t__ make_disks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

nvlist_t *
make_root_vdev(zpool_handle_t *zhp, int force, int check_rep,
    boolean_t replacing, boolean_t dryrun, zpool_boot_label_t boot_type,
    uint64_t boot_size, int argc, char **argv)
{
	nvlist_t *newroot;
	nvlist_t *poolconfig = NULL;
	is_force = force;

	/*
	 * Construct the vdev specification.  If this is successful, we know
	 * that we have a valid specification, and that all devices can be
	 * opened.
	 */
	if ((newroot = construct_spec(argc, argv)) == NULL)
		return (NULL);

	if (zhp && ((poolconfig = zpool_get_config(zhp, NULL)) == NULL))
		return (NULL);

	/*
	 * Validate each device to make sure that its not shared with another
	 * subsystem.  We do this even if 'force' is set, because there are some
	 * uses (such as a dedicated dump device) that even '-f' cannot
	 * override.
	 */
	if (is_device_in_use(poolconfig, newroot, force, replacing, B_FALSE)) {
		nvlist_free(newroot);
		return (NULL);
	}

	/*
	 * Check the replication level of the given vdevs and report any errors
	 * found.  We include the existing pool spec, if any, as we need to
	 * catch changes against the existing replication level.
	 */
	if (check_rep && check_replication(poolconfig, newroot) != 0) {
		nvlist_free(newroot);
		return (NULL);
	}

#ifdef illumos
	/*
	 * Run through the vdev specification and label any whole disks found.
	 */
	if (!dryrun && make_disks(zhp, newroot, boot_type, boot_size) != 0) {
		nvlist_free(newroot);
		return (NULL);
	}
#endif

	return (newroot);
}