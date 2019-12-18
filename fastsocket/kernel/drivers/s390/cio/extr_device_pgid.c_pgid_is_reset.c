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
struct pgid {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int pgid_is_reset(struct pgid *p)
{
	char *c;

	for (c = (char *)p + 1; c < (char *)(p + 1); c++) {
		if (*c != 0)
			return 0;
	}
	return 1;
}