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

/* Variables and functions */
#define  NCP_IOC_CONN_LOGGED_IN 146 
#define  NCP_IOC_GETCHARSETS 145 
#define  NCP_IOC_GETDENTRYTTL 144 
#define  NCP_IOC_GETMOUNTUID2 143 
#define  NCP_IOC_GETOBJECTNAME 142 
#define  NCP_IOC_GETPRIVATEDATA 141 
#define  NCP_IOC_GETROOT 140 
#define  NCP_IOC_GET_FS_INFO 139 
#define  NCP_IOC_GET_FS_INFO_V2 138 
#define  NCP_IOC_LOCKUNLOCK 137 
#define  NCP_IOC_NCPREQUEST 136 
#define  NCP_IOC_SETCHARSETS 135 
#define  NCP_IOC_SETDENTRYTTL 134 
#define  NCP_IOC_SETOBJECTNAME 133 
#define  NCP_IOC_SETPRIVATEDATA 132 
#define  NCP_IOC_SETROOT 131 
#define  NCP_IOC_SET_SIGN_WANTED 130 
#define  NCP_IOC_SIGN_INIT 129 
#define  NCP_IOC_SIGN_WANTED 128 

__attribute__((used)) static int ncp_ioctl_need_write(unsigned int cmd)
{
	switch (cmd) {
	case NCP_IOC_GET_FS_INFO:
	case NCP_IOC_GET_FS_INFO_V2:
	case NCP_IOC_NCPREQUEST:
	case NCP_IOC_SETDENTRYTTL:
	case NCP_IOC_SIGN_INIT:
	case NCP_IOC_LOCKUNLOCK:
	case NCP_IOC_SET_SIGN_WANTED:
		return 1;
	case NCP_IOC_GETOBJECTNAME:
	case NCP_IOC_SETOBJECTNAME:
	case NCP_IOC_GETPRIVATEDATA:
	case NCP_IOC_SETPRIVATEDATA:
	case NCP_IOC_SETCHARSETS:
	case NCP_IOC_GETCHARSETS:
	case NCP_IOC_CONN_LOGGED_IN:
	case NCP_IOC_GETDENTRYTTL:
	case NCP_IOC_GETMOUNTUID2:
	case NCP_IOC_SIGN_WANTED:
	case NCP_IOC_GETROOT:
	case NCP_IOC_SETROOT:
		return 0;
	default:
		/* unkown IOCTL command, assume write */
		return 1;
	}
}