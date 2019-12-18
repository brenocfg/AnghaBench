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
struct ring_buffer {int /*<<< orphan*/  writable; } ;

/* Variables and functions */
 int perf_data_size (struct ring_buffer*) ; 

__attribute__((used)) static bool perf_output_space(struct ring_buffer *rb, unsigned long tail,
			      unsigned long offset, unsigned long head)
{
	unsigned long mask;

	if (!rb->writable)
		return true;

	mask = perf_data_size(rb) - 1;

	offset = (offset - tail) & mask;
	head   = (head   - tail) & mask;

	if ((int)(head - offset) < 0)
		return false;

	return true;
}