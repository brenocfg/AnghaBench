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
 unsigned short* crctab ; 

__attribute__((used)) static unsigned short l2c_fcr_updcrc(unsigned short icrc, unsigned char *icp, int icnt)
{
    register unsigned short crc = icrc;
    register unsigned char  *cp = icp;
    register          int   cnt = icnt;

    while (cnt--) {
        crc = ((crc >> 8) & 0xff) ^ crctab[(crc & 0xff) ^ *cp++];
    }

    return (crc);
}