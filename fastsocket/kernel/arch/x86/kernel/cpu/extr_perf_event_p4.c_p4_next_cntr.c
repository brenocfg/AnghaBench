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
struct p4_event_bind {int** cntr; } ;

/* Variables and functions */
 int P4_CNTR_LIMIT ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 

__attribute__((used)) static int p4_next_cntr(int thread, unsigned long *used_mask,
			struct p4_event_bind *bind)
{
	int i, j;

	for (i = 0; i < P4_CNTR_LIMIT; i++) {
		j = bind->cntr[thread][i];
		if (j != -1 && !test_bit(j, used_mask))
			return j;
	}

	return -1;
}