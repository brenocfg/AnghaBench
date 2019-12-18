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
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 long ENOTTY ; 
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
 long openprom_ioctl (int /*<<< orphan*/ ,struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static long openprom_compat_ioctl(struct file *file, unsigned int cmd,
		unsigned long arg)
{
	long rval = -ENOTTY;

	/*
	 * SunOS/Solaris only, the NetBSD one's have embedded pointers in
	 * the arg which we'd need to clean up...
	 */
	switch (cmd) {
	case OPROMGETOPT:
	case OPROMSETOPT:
	case OPROMNXTOPT:
	case OPROMSETOPT2:
	case OPROMNEXT:
	case OPROMCHILD:
	case OPROMGETPROP:
	case OPROMNXTPROP:
	case OPROMU2P:
	case OPROMGETCONS:
	case OPROMGETFBNAME:
	case OPROMGETBOOTARGS:
	case OPROMSETCUR:
	case OPROMPCI2NODE:
	case OPROMPATH2NODE:
		rval = openprom_ioctl(file->f_path.dentry->d_inode, file, cmd, arg);
		break;
	}

	return rval;
}