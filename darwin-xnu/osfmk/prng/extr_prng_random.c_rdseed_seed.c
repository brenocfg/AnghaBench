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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  rdseed_retry (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static size_t
rdseed_seed(void * buf, size_t nwords)
{
	uint64_t * buf_words;
	size_t i;

	if (nwords > 8) {
		nwords = 8;
	}

	buf_words = buf;
	for (i = 0; i < nwords; i += 1) {
		if (!rdseed_retry(buf_words + i, 10)) {
			return i;
		}
	}

	return nwords;
}