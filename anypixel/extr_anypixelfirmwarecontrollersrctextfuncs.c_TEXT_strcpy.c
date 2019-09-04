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

int TEXT_strcpy(uint8_t *buf, const char *inStr) {
	int i = 0;
	while(inStr[i] != 0) {
		buf[i] = inStr[i];
		i++;
	}
	return i;
}