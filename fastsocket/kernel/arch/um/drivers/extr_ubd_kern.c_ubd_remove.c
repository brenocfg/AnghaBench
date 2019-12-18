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
struct ubd {scalar_t__ count; int /*<<< orphan*/  pdev; int /*<<< orphan*/ * file; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  del_gendisk (struct gendisk*) ; 
 struct gendisk** fake_gendisk ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 struct ubd* ubd_devs ; 
 struct gendisk** ubd_gendisk ; 
 int /*<<< orphan*/  ubd_lock ; 

__attribute__((used)) static int ubd_remove(int n, char **error_out)
{
	struct gendisk *disk = ubd_gendisk[n];
	struct ubd *ubd_dev;
	int err = -ENODEV;

	mutex_lock(&ubd_lock);

	ubd_dev = &ubd_devs[n];

	if(ubd_dev->file == NULL)
		goto out;

	/* you cannot remove a open disk */
	err = -EBUSY;
	if(ubd_dev->count > 0)
		goto out;

	ubd_gendisk[n] = NULL;
	if(disk != NULL){
		del_gendisk(disk);
		put_disk(disk);
	}

	if(fake_gendisk[n] != NULL){
		del_gendisk(fake_gendisk[n]);
		put_disk(fake_gendisk[n]);
		fake_gendisk[n] = NULL;
	}

	err = 0;
	platform_device_unregister(&ubd_dev->pdev);
out:
	mutex_unlock(&ubd_lock);
	return err;
}