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
#define  SCECdCDDA 141 
#define  SCECdDETCT 140 
#define  SCECdDETCTCD 139 
#define  SCECdDETCTDVDD 138 
#define  SCECdDETCTDVDS 137 
#define  SCECdDVDV 136 
#define  SCECdIllegalMedia 135 
#define  SCECdNODISC 134 
#define  SCECdPS2CD 133 
#define  SCECdPS2CDDA 132 
#define  SCECdPS2DVD 131 
#define  SCECdPSCD 130 
#define  SCECdPSCDDA 129 
#define  SCECdUNKNOWN 128 
 int sceCdGetDiskType () ; 

__attribute__((used)) static int ps2_cdDiscValid(void)  //returns 1 if disc valid, else returns 0
{
	int cdmode = sceCdGetDiskType();

	switch (cdmode) {
		case SCECdPSCD:
		case SCECdPSCDDA:
		case SCECdPS2CD:
		case SCECdPS2CDDA:
		case SCECdPS2DVD:
		case SCECdCDDA:
		case SCECdDVDV:
			return 1;
		case SCECdNODISC:
		case SCECdDETCT:
		case SCECdDETCTCD:
		case SCECdDETCTDVDS:
		case SCECdDETCTDVDD:
		case SCECdUNKNOWN:
		case SCECdIllegalMedia:
		default:
			return 0;
	}
}