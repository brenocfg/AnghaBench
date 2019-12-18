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
struct scatterlist {scalar_t__ length; } ;

/* Variables and functions */

__attribute__((used)) static int count_sgs(struct scatterlist *sl, unsigned int total_bytes)
{
	int i = 0;

	do {
		total_bytes -= sl[i].length;
		i++;

	} while (total_bytes > 0);

	return i;
}