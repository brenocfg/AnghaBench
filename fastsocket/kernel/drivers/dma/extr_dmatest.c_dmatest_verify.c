#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 unsigned int PATTERN_COUNT_MASK ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dmatest_mismatch (unsigned int,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int dmatest_verify(u8 **bufs, unsigned int start,
		unsigned int end, unsigned int counter, u8 pattern,
		bool is_srcbuf)
{
	unsigned int i;
	unsigned int error_count = 0;
	u8 actual;
	u8 expected;
	u8 *buf;
	unsigned int counter_orig = counter;

	for (; (buf = *bufs); bufs++) {
		counter = counter_orig;
		for (i = start; i < end; i++) {
			actual = buf[i];
			expected = pattern | (~counter & PATTERN_COUNT_MASK);
			if (actual != expected) {
				if (error_count < 32)
					dmatest_mismatch(actual, pattern, i,
							 counter, is_srcbuf);
				error_count++;
			}
			counter++;
		}
	}

	if (error_count > 32)
		pr_warning("%s: %u errors suppressed\n",
			current->comm, error_count - 32);

	return error_count;
}