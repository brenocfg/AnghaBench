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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 

u8 rtl8192SU_UsbOptionToEndPointNumber(u8 UsbOption)
{
	u8	nEndPoint = 0;
	switch(UsbOption)
	{
		case 0:
			nEndPoint = 6;
			break;
		case 1:
			nEndPoint = 11;
			break;
		case 2:
			nEndPoint = 4;
			break;
		default:
			RT_TRACE(COMP_INIT, "UsbOptionToEndPointNumber(): Invalid UsbOption(%#x)\n", UsbOption);
			break;
	}
	return nEndPoint;
}