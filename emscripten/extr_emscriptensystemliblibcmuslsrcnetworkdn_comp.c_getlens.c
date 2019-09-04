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

__attribute__((used)) static int getlens(unsigned char *lens, const char *s, int l)
{
	int i=0,j=0,k=0;
	for (;;) {
		for (; j<l && s[j]!='.'; j++);
		if (j-k-1u > 62) return 0;
		lens[i++] = j-k;
		if (j==l) return i;
		k = ++j;
	}
}