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
struct CHIPSTATE {int dummy; } ;

/* Variables and functions */
 int TDA985x_SAPP ; 
 int TDA985x_STP ; 
 int V4L2_TUNER_MODE_MONO ; 
 int chip_read (struct CHIPSTATE*) ; 

__attribute__((used)) static int  tda985x_getmode(struct CHIPSTATE *chip)
{
	int mode;

	mode = ((TDA985x_STP | TDA985x_SAPP) &
		chip_read(chip)) >> 4;
	/* Add mono mode regardless of SAP and stereo */
	/* Allows forced mono */
	return mode | V4L2_TUNER_MODE_MONO;
}