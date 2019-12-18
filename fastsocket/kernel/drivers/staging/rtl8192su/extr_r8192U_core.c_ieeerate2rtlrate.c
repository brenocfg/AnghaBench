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
typedef  int u16 ;

/* Variables and functions */

inline u16 ieeerate2rtlrate(int rate)
{
	switch(rate){
	case 10:
	return 0;
	case 20:
	return 1;
	case 55:
	return 2;
	case 110:
	return 3;
	case 60:
	return 4;
	case 90:
	return 5;
	case 120:
	return 6;
	case 180:
	return 7;
	case 240:
	return 8;
	case 360:
	return 9;
	case 480:
	return 10;
	case 540:
	return 11;
	default:
	return 3;

	}
}