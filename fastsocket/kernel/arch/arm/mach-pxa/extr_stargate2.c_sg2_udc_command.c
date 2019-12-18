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
#define  PXA2XX_UDC_CMD_CONNECT 129 
#define  PXA2XX_UDC_CMD_DISCONNECT 128 
 int UP2OCR ; 
 int UP2OCR_DPPUBE ; 
 int UP2OCR_DPPUE ; 
 int UP2OCR_HXOE ; 

__attribute__((used)) static void sg2_udc_command(int cmd)
{
	switch (cmd) {
	case PXA2XX_UDC_CMD_CONNECT:
		UP2OCR |=  UP2OCR_HXOE  | UP2OCR_DPPUE | UP2OCR_DPPUBE;
		break;
	case PXA2XX_UDC_CMD_DISCONNECT:
		UP2OCR &= ~(UP2OCR_HXOE  | UP2OCR_DPPUE | UP2OCR_DPPUBE);
		break;
	}
}