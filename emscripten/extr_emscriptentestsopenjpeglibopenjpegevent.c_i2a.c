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

__attribute__((used)) static char*
i2a(unsigned i, char *a, unsigned r) {
	if (i/r > 0) a = i2a(i/r,a,r);
	*a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i%r];
	return a+1;
}