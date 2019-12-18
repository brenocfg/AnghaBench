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

__attribute__((used)) static int xn(char *buf, int offs, int size)
{
	int v, k;

	v = 0;
	for (k = 0; k < size; k++)
		v = v * 256 + (buf[k + offs] & 0xff);
	return v;
}