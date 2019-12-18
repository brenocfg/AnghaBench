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
struct file {int f_mode; scalar_t__ private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * current_node; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int EBADF ; 
 int EINVAL ; 
 int EPERM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
#define  OPIOCGET 148 
#define  OPIOCGETCHILD 147 
#define  OPIOCGETNEXT 146 
#define  OPIOCGETOPTNODE 145 
#define  OPIOCNEXTPROP 144 
#define  OPIOCSET 143 
#define  OPROMCHILD 142 
#define  OPROMGETBOOTARGS 141 
#define  OPROMGETCONS 140 
#define  OPROMGETFBNAME 139 
#define  OPROMGETOPT 138 
#define  OPROMGETPROP 137 
#define  OPROMNEXT 136 
#define  OPROMNXTOPT 135 
#define  OPROMNXTPROP 134 
#define  OPROMPATH2NODE 133 
#define  OPROMPCI2NODE 132 
#define  OPROMSETCUR 131 
#define  OPROMSETOPT 130 
#define  OPROMSETOPT2 129 
#define  OPROMU2P 128 
 int openprom_bsd_ioctl (struct inode*,struct file*,unsigned int,unsigned long) ; 
 int openprom_sunos_ioctl (struct inode*,struct file*,unsigned int,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * options_node ; 

__attribute__((used)) static int openprom_ioctl(struct inode * inode, struct file * file,
			  unsigned int cmd, unsigned long arg)
{
	DATA *data = (DATA *) file->private_data;

	switch (cmd) {
	case OPROMGETOPT:
	case OPROMNXTOPT:
		if ((file->f_mode & FMODE_READ) == 0)
			return -EPERM;
		return openprom_sunos_ioctl(inode, file, cmd, arg,
					    options_node);

	case OPROMSETOPT:
	case OPROMSETOPT2:
		if ((file->f_mode & FMODE_WRITE) == 0)
			return -EPERM;
		return openprom_sunos_ioctl(inode, file, cmd, arg,
					    options_node);

	case OPROMNEXT:
	case OPROMCHILD:
	case OPROMGETPROP:
	case OPROMNXTPROP:
		if ((file->f_mode & FMODE_READ) == 0)
			return -EPERM;
		return openprom_sunos_ioctl(inode, file, cmd, arg,
					    data->current_node);

	case OPROMU2P:
	case OPROMGETCONS:
	case OPROMGETFBNAME:
	case OPROMGETBOOTARGS:
	case OPROMSETCUR:
	case OPROMPCI2NODE:
	case OPROMPATH2NODE:
		if ((file->f_mode & FMODE_READ) == 0)
			return -EPERM;
		return openprom_sunos_ioctl(inode, file, cmd, arg, NULL);

	case OPIOCGET:
	case OPIOCNEXTPROP:
	case OPIOCGETOPTNODE:
	case OPIOCGETNEXT:
	case OPIOCGETCHILD:
		if ((file->f_mode & FMODE_READ) == 0)
			return -EBADF;
		return openprom_bsd_ioctl(inode,file,cmd,arg);

	case OPIOCSET:
		if ((file->f_mode & FMODE_WRITE) == 0)
			return -EBADF;
		return openprom_bsd_ioctl(inode,file,cmd,arg);

	default:
		return -EINVAL;
	};
}