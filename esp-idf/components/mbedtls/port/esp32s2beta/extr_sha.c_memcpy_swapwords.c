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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void memcpy_swapwords(void *to, const void *from, size_t num_bytes)
{
    uint32_t *to_words = (uint32_t *)to;
    const uint32_t *from_words = (const uint32_t *)from;
    assert(num_bytes % 8 == 0);
    for (int i = 0; i < num_bytes / 4; i += 2) {
        to_words[i] = from_words[i+1];
        to_words[i+1] = from_words[i];
    }
    asm volatile ("memw");
}