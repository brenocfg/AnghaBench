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
struct rackmeter {int* ubuf; } ;

/* Variables and functions */

__attribute__((used)) static void rackmeter_set_default_pattern(struct rackmeter *rm)
{
	int i;

	for (i = 0; i < 16; i++) {
		if (i < 8)
			rm->ubuf[i] = (i & 1) * 255;
		else
			rm->ubuf[i] = ((~i) & 1) * 255;
	}
}