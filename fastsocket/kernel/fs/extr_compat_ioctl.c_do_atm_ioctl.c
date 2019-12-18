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
struct TYPE_2__ {unsigned int cmd32; unsigned int cmd; } ;

/* Variables and functions */
#define  ATM_ADDADDR 152 
#define  ATM_DELADDR 151 
#define  ATM_GETADDR 150 
#define  ATM_GETCIRANGE 149 
#define  ATM_GETESI 148 
#define  ATM_GETLINKRATE 147 
#define  ATM_GETLOOP 146 
#define  ATM_GETNAMES 145 
#define  ATM_GETSTAT 144 
#define  ATM_GETSTATZ 143 
#define  ATM_GETTYPE 142 
#define  ATM_QUERYLOOP 141 
#define  ATM_RSTADDR 140 
#define  ATM_SETCIRANGE 139 
#define  ATM_SETESI 138 
#define  ATM_SETESIF 137 
#define  ATM_SETLOOP 136 
 int EINVAL ; 
 int NR_ATM_IOCTL ; 
#define  SONET_CLRDIAG 135 
#define  SONET_GETDIAG 134 
#define  SONET_GETFRAMING 133 
#define  SONET_GETFRSENSE 132 
#define  SONET_GETSTAT 131 
#define  SONET_GETSTATZ 130 
#define  SONET_SETDIAG 129 
#define  SONET_SETFRAMING 128 
 TYPE_1__* atm_ioctl_map ; 
 int do_atm_iobuf (unsigned int,unsigned int,unsigned long) ; 
 int do_atmif_sioc (unsigned int,unsigned int,unsigned long) ; 

__attribute__((used)) static int do_atm_ioctl(unsigned int fd, unsigned int cmd32, unsigned long arg)
{
        int i;
        unsigned int cmd = 0;
        
	switch (cmd32) {
	case SONET_GETSTAT:
	case SONET_GETSTATZ:
	case SONET_GETDIAG:
	case SONET_SETDIAG:
	case SONET_CLRDIAG:
	case SONET_SETFRAMING:
	case SONET_GETFRAMING:
	case SONET_GETFRSENSE:
		return do_atmif_sioc(fd, cmd32, arg);
	}

	for (i = 0; i < NR_ATM_IOCTL; i++) {
		if (cmd32 == atm_ioctl_map[i].cmd32) {
			cmd = atm_ioctl_map[i].cmd;
			break;
		}
	}
	if (i == NR_ATM_IOCTL)
	        return -EINVAL;
        
        switch (cmd) {
	case ATM_GETNAMES:
		return do_atm_iobuf(fd, cmd, arg);
	    
	case ATM_GETLINKRATE:
        case ATM_GETTYPE:
        case ATM_GETESI:
        case ATM_GETADDR:
        case ATM_RSTADDR:
        case ATM_ADDADDR:
        case ATM_DELADDR:
        case ATM_GETCIRANGE:
	case ATM_SETCIRANGE:
	case ATM_SETESI:
	case ATM_SETESIF:
	case ATM_GETSTAT:
	case ATM_GETSTATZ:
	case ATM_GETLOOP:
	case ATM_SETLOOP:
	case ATM_QUERYLOOP:
                return do_atmif_sioc(fd, cmd, arg);
        }

        return -EINVAL;
}