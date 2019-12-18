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
struct hdsp {int control_register; } ;

/* Variables and functions */
#define  HDSP_PhoneGain0dB 130 
 int HDSP_PhoneGainMask ; 
#define  HDSP_PhoneGainMinus12dB 129 
#define  HDSP_PhoneGainMinus6dB 128 

__attribute__((used)) static int hdsp_phone_gain(struct hdsp *hdsp)
{
	switch (hdsp->control_register & HDSP_PhoneGainMask) {
	case HDSP_PhoneGain0dB:
		return 0;
	case HDSP_PhoneGainMinus6dB:
		return 1;
	case HDSP_PhoneGainMinus12dB:
		return 2;
	default:
		return 0;
	}
}