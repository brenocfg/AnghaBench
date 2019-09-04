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

__attribute__((used)) static inline int
necp_count_dots(char *string, size_t length)
{
	int dot_count = 0;
	size_t i = 0;

	for (i = 0; i < length; i++) {
		if (string[i] == '.') {
			dot_count++;
		}
	}

	return (dot_count);
}