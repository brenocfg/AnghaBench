#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ status; int /*<<< orphan*/  lock; struct socket* tcp_socket; } ;
struct vhci_device {TYPE_1__ ud; void* speed; void* devid; } ;
struct socket {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
typedef  void* __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ VDEV_ST_NOTASSIGNED ; 
 scalar_t__ VDEV_ST_NULL ; 
 struct vhci_device* port_to_vdev (void*) ; 
 int /*<<< orphan*/  rh_port_connect (void*,void*) ; 
 struct socket* sockfd_to_socket (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,void**,int*,void**,void**) ; 
 TYPE_2__* the_controller ; 
 int /*<<< orphan*/  usbip_dbg_vhci_sysfs (char*,void*,int,void*,void*) ; 
 int /*<<< orphan*/  usbip_start_threads (TYPE_1__*) ; 
 int /*<<< orphan*/  usbip_uerr (char*,void*) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,void*,int,void*,void*) ; 
 scalar_t__ valid_args (void*,void*) ; 

__attribute__((used)) static ssize_t store_attach(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct vhci_device *vdev;
	struct socket *socket;
	int sockfd = 0;
	__u32 rhport = 0, devid = 0, speed = 0;

	/*
	 * @rhport: port number of vhci_hcd
	 * @sockfd: socket descriptor of an established TCP connection
	 * @devid: unique device identifier in a remote host
	 * @speed: usb device speed in a remote host
	 */
	sscanf(buf, "%u %u %u %u", &rhport, &sockfd, &devid, &speed);

	usbip_dbg_vhci_sysfs("rhport(%u) sockfd(%u) devid(%u) speed(%u)\n",
				rhport, sockfd, devid, speed);


	/* check received parameters */
	if (valid_args(rhport, speed) < 0)
		return -EINVAL;

	/* check sockfd */
	socket = sockfd_to_socket(sockfd);
	if (!socket)
		return  -EINVAL;

	/* now need lock until setting vdev status as used */

	/* begin a lock */
	spin_lock(&the_controller->lock);

	vdev = port_to_vdev(rhport);

	spin_lock(&vdev->ud.lock);

	if (vdev->ud.status != VDEV_ST_NULL) {
		/* end of the lock */
		spin_unlock(&vdev->ud.lock);
		spin_unlock(&the_controller->lock);

		usbip_uerr("port %d already used\n", rhport);
		return -EINVAL;
	}

	usbip_uinfo("rhport(%u) sockfd(%d) devid(%u) speed(%u)\n",
				rhport, sockfd, devid, speed);

	vdev->devid         = devid;
	vdev->speed         = speed;
	vdev->ud.tcp_socket = socket;
	vdev->ud.status     = VDEV_ST_NOTASSIGNED;

	spin_unlock(&vdev->ud.lock);
	spin_unlock(&the_controller->lock);
	/* end the lock */

	/*
	 * this function will sleep, so should be out of the lock. but, it's ok
	 * because we already marked vdev as being used. really?
	 */
	usbip_start_threads(&vdev->ud);

	rh_port_connect(rhport, speed);

	return count;
}