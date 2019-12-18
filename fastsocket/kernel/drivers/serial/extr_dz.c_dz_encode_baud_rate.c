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
 int DZ_B110 ; 
 int DZ_B1200 ; 
 int DZ_B134 ; 
 int DZ_B150 ; 
 int DZ_B1800 ; 
 int DZ_B2000 ; 
 int DZ_B2400 ; 
 int DZ_B300 ; 
 int DZ_B3600 ; 
 int DZ_B4800 ; 
 int DZ_B50 ; 
 int DZ_B600 ; 
 int DZ_B7200 ; 
 int DZ_B75 ; 
 int DZ_B9600 ; 

__attribute__((used)) static int dz_encode_baud_rate(unsigned int baud)
{
	switch (baud) {
	case 50:
		return DZ_B50;
	case 75:
		return DZ_B75;
	case 110:
		return DZ_B110;
	case 134:
		return DZ_B134;
	case 150:
		return DZ_B150;
	case 300:
		return DZ_B300;
	case 600:
		return DZ_B600;
	case 1200:
		return DZ_B1200;
	case 1800:
		return DZ_B1800;
	case 2000:
		return DZ_B2000;
	case 2400:
		return DZ_B2400;
	case 3600:
		return DZ_B3600;
	case 4800:
		return DZ_B4800;
	case 7200:
		return DZ_B7200;
	case 9600:
		return DZ_B9600;
	default:
		return -1;
	}
}