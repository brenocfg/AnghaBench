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
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct adsp_device {scalar_t__ device; } ;

/* Variables and functions */
 unsigned int MINOR (int /*<<< orphan*/ ) ; 
 unsigned int adsp_device_count ; 
 struct adsp_device* adsp_devices ; 

__attribute__((used)) static struct adsp_device *inode_to_device(struct inode *inode)
{
	unsigned n = MINOR(inode->i_rdev);
	if (n < adsp_device_count) {
		if (adsp_devices[n].device)
			return adsp_devices + n;
	}
	return NULL;
}