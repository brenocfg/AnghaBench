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
struct net_device {TYPE_1__* wireless_handlers; } ;
struct iw_priv_args {unsigned int cmd; char* name; int set_args; int get_args; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int num_private_args; struct iw_priv_args* private_args; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 scalar_t__ IW_IS_SET (unsigned int) ; 
 int IW_PRIV_SIZE_FIXED ; 
 int get_priv_size (int) ; 

__attribute__((used)) static int get_priv_descr_and_size(struct net_device *dev, unsigned int cmd,
				   const struct iw_priv_args **descrp)
{
	const struct iw_priv_args *descr;
	int i, extra_size;

	descr = NULL;
	for (i = 0; i < dev->wireless_handlers->num_private_args; i++) {
		if (cmd == dev->wireless_handlers->private_args[i].cmd) {
			descr = &dev->wireless_handlers->private_args[i];
			break;
		}
	}

	extra_size = 0;
	if (descr) {
		if (IW_IS_SET(cmd)) {
			int	offset = 0;	/* For sub-ioctls */
			/* Check for sub-ioctl handler */
			if (descr->name[0] == '\0')
				/* Reserve one int for sub-ioctl index */
				offset = sizeof(__u32);

			/* Size of set arguments */
			extra_size = get_priv_size(descr->set_args);

			/* Does it fits in iwr ? */
			if ((descr->set_args & IW_PRIV_SIZE_FIXED) &&
			   ((extra_size + offset) <= IFNAMSIZ))
				extra_size = 0;
		} else {
			/* Size of get arguments */
			extra_size = get_priv_size(descr->get_args);

			/* Does it fits in iwr ? */
			if ((descr->get_args & IW_PRIV_SIZE_FIXED) &&
			   (extra_size <= IFNAMSIZ))
				extra_size = 0;
		}
	}
	*descrp = descr;
	return extra_size;
}