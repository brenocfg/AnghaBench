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
struct iw_freq {scalar_t__ i; int /*<<< orphan*/  m; } ;

/* Variables and functions */

__attribute__((used)) static inline void sort_channels(struct iw_freq *freq, int num)
{
	int i, j;
	struct iw_freq temp;

	for (i = 0; i < num; i++)
		for (j = i + 1; j < num; j++)
			if (freq[i].i > freq[j].i) {
				temp.i = freq[i].i;
				temp.m = freq[i].m;

				freq[i].i = freq[j].i;
				freq[i].m = freq[j].m;

				freq[j].i = temp.i;
				freq[j].m = temp.m;
			}
}