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
typedef  char const uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

int TEXT_strncmp(uint8_t *buf, const char *inStr, uint16_t num) {
	int i;
	int retval;
	for(i = 0; i < num; i++) {
		retval = buf[i] - inStr[i];
		if(retval != 0)
			return retval;
	}
	return 0;
}