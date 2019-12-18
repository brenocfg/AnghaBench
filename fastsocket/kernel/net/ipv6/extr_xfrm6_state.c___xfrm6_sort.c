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
typedef  int /*<<< orphan*/  count ;

/* Variables and functions */
 int XFRM_MAX_DEPTH ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
__xfrm6_sort(void **dst, void **src, int n, int (*cmp)(void *p), int maxclass)
{
	int i;
	int class[XFRM_MAX_DEPTH];
	int count[maxclass];

	memset(count, 0, sizeof(count));

	for (i = 0; i < n; i++) {
		int c;
		class[i] = c = cmp(src[i]);
		count[c]++;
	}

	for (i = 2; i < maxclass; i++)
		count[i] += count[i - 1];

	for (i = 0; i < n; i++) {
		dst[count[class[i] - 1]++] = src[i];
		src[i] = NULL;
	}

	return 0;
}