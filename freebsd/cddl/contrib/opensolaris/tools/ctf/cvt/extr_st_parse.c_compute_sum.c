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
 int HASH (int) ; 

__attribute__((used)) static int
compute_sum(const char *w)
{
	char c;
	int sum;

	for (sum = 0; (c = *w) != '\0'; sum += c, w++)
		;
	return (HASH(sum));
}