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
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static int
int64width(int64_t val)
{
	int len;

	len = 0;
	/* Negative or zero values require one extra digit. */
	if (val <= 0) {
		val = -val;
		len++;
	}
	while (val > 0) {
		len++;
		val /= 10;
	}

	return (len);
}