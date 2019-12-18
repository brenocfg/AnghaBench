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
 unsigned int csum_partial (char const*,int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

unsigned int csum_partial_copy(const char *src, char *dst,
				int len, unsigned int sum)
{
	sum = csum_partial(src, len, sum);
	memcpy(dst, src, len);

	return sum;
}