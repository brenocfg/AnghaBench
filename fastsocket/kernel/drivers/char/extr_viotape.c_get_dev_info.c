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
struct viot_devinfo_struct {int devno; int mode; int rewind; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int iminor (struct inode*) ; 

void get_dev_info(struct inode *ino, struct viot_devinfo_struct *devi)
{
	devi->devno = iminor(ino) & 0x1F;
	devi->mode = (iminor(ino) & 0x60) >> 5;
	/* if bit is set in the minor, do _not_ rewind automatically */
	devi->rewind = (iminor(ino) & 0x80) == 0;
}