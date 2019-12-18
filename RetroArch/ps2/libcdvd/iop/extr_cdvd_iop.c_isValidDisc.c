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
#define  SCECdPS2CD 132 
#define  SCECdPS2CDDA 131 
#define  SCECdPS2DVD 130 
#define  SCECdPSCD 129 
#define  SCECdPSCDDA 128 
 int sceCdGetDiskType () ; 

int isValidDisc(void)
{
    int result;

    switch (sceCdGetDiskType()) {
        case SCECdPSCD:
        case SCECdPSCDDA:
        case SCECdPS2CD:
        case SCECdPS2CDDA:
        case SCECdPS2DVD:
            result = 1;
            break;
        default:
            result = 0;
    }

    return result;
}