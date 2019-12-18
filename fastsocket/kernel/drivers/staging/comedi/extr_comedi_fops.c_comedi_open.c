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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct comedi_device_file_info {struct comedi_device* device; } ;
struct comedi_device {int in_request_module; scalar_t__ use_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  (* open ) (struct comedi_device*) ;scalar_t__ attached; TYPE_1__* driver; int /*<<< orphan*/  minor; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  COMEDI_MAJOR ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct comedi_device_file_info* comedi_get_device_file_info (unsigned int const) ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int comedi_open(struct inode *inode, struct file *file)
{
	const unsigned minor = iminor(inode);
	struct comedi_device_file_info *dev_file_info =
	    comedi_get_device_file_info(minor);
	struct comedi_device *dev =
	    dev_file_info ? dev_file_info->device : NULL;

	if (dev == NULL) {
		DPRINTK("invalid minor number\n");
		return -ENODEV;
	}

	/* This is slightly hacky, but we want module autoloading
	 * to work for root.
	 * case: user opens device, attached -> ok
	 * case: user opens device, unattached, in_request_module=0 -> autoload
	 * case: user opens device, unattached, in_request_module=1 -> fail
	 * case: root opens device, attached -> ok
	 * case: root opens device, unattached, in_request_module=1 -> ok
	 *   (typically called from modprobe)
	 * case: root opens device, unattached, in_request_module=0 -> autoload
	 *
	 * The last could be changed to "-> ok", which would deny root
	 * autoloading.
	 */
	mutex_lock(&dev->mutex);
	if (dev->attached)
		goto ok;
	if (!capable(CAP_NET_ADMIN) && dev->in_request_module) {
		DPRINTK("in request module\n");
		mutex_unlock(&dev->mutex);
		return -ENODEV;
	}
	if (capable(CAP_NET_ADMIN) && dev->in_request_module)
		goto ok;

	dev->in_request_module = 1;

#ifdef CONFIG_KMOD
	mutex_unlock(&dev->mutex);
	request_module("char-major-%i-%i", COMEDI_MAJOR, dev->minor);
	mutex_lock(&dev->mutex);
#endif

	dev->in_request_module = 0;

	if (!dev->attached && !capable(CAP_NET_ADMIN)) {
		DPRINTK("not attached and not CAP_NET_ADMIN\n");
		mutex_unlock(&dev->mutex);
		return -ENODEV;
	}
ok:
	__module_get(THIS_MODULE);

	if (dev->attached) {
		if (!try_module_get(dev->driver->module)) {
			module_put(THIS_MODULE);
			mutex_unlock(&dev->mutex);
			return -ENOSYS;
		}
	}

	if (dev->attached && dev->use_count == 0 && dev->open)
		dev->open(dev);

	dev->use_count++;

	mutex_unlock(&dev->mutex);

	return 0;
}