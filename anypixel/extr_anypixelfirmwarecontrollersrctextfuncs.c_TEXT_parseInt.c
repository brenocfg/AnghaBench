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
typedef  char uint8_t ;

/* Variables and functions */

uint8_t TEXT_parseInt(uint8_t *buf, int *result) {
	uint8_t offset = 0;
	bool negative = false;
	if(buf[0] == '-') {
		negative = true;
		offset++;
	}
	*result = 0;
	while(buf[offset] >= '0' && buf[offset] <= '9') {
		*result *= 10;
		*result += buf[offset++] - '0';
	}
	if(negative)
		*result *= -1;
	return offset;
}