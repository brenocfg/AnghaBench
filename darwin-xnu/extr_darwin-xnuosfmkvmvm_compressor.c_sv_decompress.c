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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void sv_decompress(int32_t *ddst, int32_t pattern) {
#if __x86_64__
			memset_word(ddst, pattern, PAGE_SIZE / sizeof(int32_t));
#else
			size_t		i;

			/* Unroll the pattern fill loop 4x to encourage the
			 * compiler to emit NEON stores, cf.
			 * <rdar://problem/25839866> Loop autovectorization
			 * anomalies.
			 * We use separate loops for each PAGE_SIZE
			 * to allow the autovectorizer to engage, as PAGE_SIZE
			 * is currently not a constant.
			 */

			__unreachable_ok_push
			if (PAGE_SIZE == 4096) {
				for (i = 0; i < (4096U / sizeof(int32_t)); i += 4) {
					*ddst++ = pattern;
					*ddst++ = pattern;
					*ddst++ = pattern;
					*ddst++ = pattern;
				}
			} else {
				assert(PAGE_SIZE == 16384);
				for (i = 0; i < (int)(16384U / sizeof(int32_t)); i += 4) {
					*ddst++ = pattern;
					*ddst++ = pattern;
					*ddst++ = pattern;
					*ddst++ = pattern;
				}
			}
			__unreachable_ok_pop
#endif
}