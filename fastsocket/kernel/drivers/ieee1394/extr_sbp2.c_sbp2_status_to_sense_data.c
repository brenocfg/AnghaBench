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
typedef  int unchar ;

/* Variables and functions */

__attribute__((used)) static unsigned int sbp2_status_to_sense_data(unchar *sbp2_status,
					      unchar *sense_data)
{
	/* OK, it's pretty ugly... ;-) */
	sense_data[0] = 0x70;
	sense_data[1] = 0x0;
	sense_data[2] = sbp2_status[9];
	sense_data[3] = sbp2_status[12];
	sense_data[4] = sbp2_status[13];
	sense_data[5] = sbp2_status[14];
	sense_data[6] = sbp2_status[15];
	sense_data[7] = 10;
	sense_data[8] = sbp2_status[16];
	sense_data[9] = sbp2_status[17];
	sense_data[10] = sbp2_status[18];
	sense_data[11] = sbp2_status[19];
	sense_data[12] = sbp2_status[10];
	sense_data[13] = sbp2_status[11];
	sense_data[14] = sbp2_status[20];
	sense_data[15] = sbp2_status[21];

	return sbp2_status[8] & 0x3f;
}