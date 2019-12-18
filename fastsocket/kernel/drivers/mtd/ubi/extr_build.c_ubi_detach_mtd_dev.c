#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubi_device {int ubi_num; int /*<<< orphan*/  dev; TYPE_1__* mtd; int /*<<< orphan*/  dbg_peb_buf; int /*<<< orphan*/  peb_buf2; int /*<<< orphan*/  peb_buf1; int /*<<< orphan*/  vtbl; scalar_t__ bgt_thread; int /*<<< orphan*/  reboot_notifier; scalar_t__ ref_count; int /*<<< orphan*/  ubi_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int UBI_MAX_DEVICES ; 
 int /*<<< orphan*/  UBI_VOLUME_REMOVED ; 
 int /*<<< orphan*/  dbg_msg (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_internal_volumes (struct ubi_device*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_mtd_device (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/ ** ubi_devices ; 
 int /*<<< orphan*/  ubi_devices_lock ; 
 int /*<<< orphan*/  ubi_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ubi_device* ubi_get_device (int) ; 
 int /*<<< orphan*/  ubi_msg (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubi_notify_all (struct ubi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_wl_close (struct ubi_device*) ; 
 int /*<<< orphan*/  uif_close (struct ubi_device*) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

int ubi_detach_mtd_dev(int ubi_num, int anyway)
{
	struct ubi_device *ubi;

	if (ubi_num < 0 || ubi_num >= UBI_MAX_DEVICES)
		return -EINVAL;

	ubi = ubi_get_device(ubi_num);
	if (!ubi)
		return -EINVAL;

	spin_lock(&ubi_devices_lock);
	put_device(&ubi->dev);
	ubi->ref_count -= 1;
	if (ubi->ref_count) {
		if (!anyway) {
			spin_unlock(&ubi_devices_lock);
			return -EBUSY;
		}
		/* This may only happen if there is a bug */
		ubi_err("%s reference count %d, destroy anyway",
			ubi->ubi_name, ubi->ref_count);
	}
	ubi_devices[ubi_num] = NULL;
	spin_unlock(&ubi_devices_lock);

	ubi_assert(ubi_num == ubi->ubi_num);
	ubi_notify_all(ubi, UBI_VOLUME_REMOVED, NULL);
	dbg_msg("detaching mtd%d from ubi%d", ubi->mtd->index, ubi_num);

	/*
	 * Before freeing anything, we have to stop the background thread to
	 * prevent it from doing anything on this device while we are freeing.
	 */
	unregister_reboot_notifier(&ubi->reboot_notifier);
	if (ubi->bgt_thread)
		kthread_stop(ubi->bgt_thread);

	/*
	 * Get a reference to the device in order to prevent 'dev_release()'
	 * from freeing @ubi object.
	 */
	get_device(&ubi->dev);

	uif_close(ubi);
	ubi_wl_close(ubi);
	free_internal_volumes(ubi);
	vfree(ubi->vtbl);
	put_mtd_device(ubi->mtd);
	vfree(ubi->peb_buf1);
	vfree(ubi->peb_buf2);
#ifdef CONFIG_MTD_UBI_DEBUG_PARANOID
	vfree(ubi->dbg_peb_buf);
#endif
	ubi_msg("mtd%d is detached from ubi%d", ubi->mtd->index, ubi->ubi_num);
	put_device(&ubi->dev);
	return 0;
}