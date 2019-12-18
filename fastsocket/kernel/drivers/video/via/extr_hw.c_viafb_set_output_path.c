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
#define  DEVICE_CRT 130 
#define  DEVICE_DVI 129 
#define  DEVICE_LCD 128 
 int /*<<< orphan*/  set_crt_output_path (int) ; 
 int /*<<< orphan*/  set_dvi_output_path (int,int) ; 
 int /*<<< orphan*/  set_lcd_output_path (int,int) ; 

void viafb_set_output_path(int device, int set_iga, int output_interface)
{
	switch (device) {
	case DEVICE_CRT:
		set_crt_output_path(set_iga);
		break;
	case DEVICE_DVI:
		set_dvi_output_path(set_iga, output_interface);
		break;
	case DEVICE_LCD:
		set_lcd_output_path(set_iga, output_interface);
		break;
	}
}