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
#define  TYPE_DISK 137 
#define  TYPE_IBM_SCSI_ADAPTER 136 
#define  TYPE_MEDIUM_CHANGER 135 
#define  TYPE_MOD 134 
#define  TYPE_NO_LUN 133 
#define  TYPE_PROCESSOR 132 
#define  TYPE_ROM 131 
#define  TYPE_SCANNER 130 
#define  TYPE_TAPE 129 
#define  TYPE_WORM 128 

__attribute__((used)) static char *ti_p(int dev)
{
	switch (dev) {
	case TYPE_IBM_SCSI_ADAPTER:
		return ("A");
	case TYPE_DISK:
		return ("D");
	case TYPE_TAPE:
		return ("T");
	case TYPE_PROCESSOR:
		return ("P");
	case TYPE_WORM:
		return ("W");
	case TYPE_ROM:
		return ("R");
	case TYPE_SCANNER:
		return ("S");
	case TYPE_MOD:
		return ("M");
	case TYPE_MEDIUM_CHANGER:
		return ("C");
	case TYPE_NO_LUN:
		return ("+");	/* show NO_LUN */
	}
	return ("-");		/* TYPE_NO_DEVICE and others */
}