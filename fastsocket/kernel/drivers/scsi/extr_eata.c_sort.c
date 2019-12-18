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

__attribute__((used)) static void sort(unsigned long sk[], unsigned int da[], unsigned int n,
		 unsigned int rev)
{
	unsigned int i, j, k, y;
	unsigned long x;

	for (i = 0; i < n - 1; i++) {
		k = i;

		for (j = k + 1; j < n; j++)
			if (rev) {
				if (sk[j] > sk[k])
					k = j;
			} else {
				if (sk[j] < sk[k])
					k = j;
			}

		if (k != i) {
			x = sk[k];
			sk[k] = sk[i];
			sk[i] = x;
			y = da[k];
			da[k] = da[i];
			da[i] = y;
		}
	}

	return;
}