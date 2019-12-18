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
 int /*<<< orphan*/  assert (int) ; 
 unsigned int const* kInverseProbabiltyLog256 ; 

__attribute__((used)) static size_t ZSTD_crossEntropyCost(short const* norm, unsigned accuracyLog,
                                    unsigned const* count, unsigned const max)
{
    unsigned const shift = 8 - accuracyLog;
    size_t cost = 0;
    unsigned s;
    assert(accuracyLog <= 8);
    for (s = 0; s <= max; ++s) {
        unsigned const normAcc = norm[s] != -1 ? norm[s] : 1;
        unsigned const norm256 = normAcc << shift;
        assert(norm256 > 0);
        assert(norm256 < 256);
        cost += count[s] * kInverseProbabiltyLog256[norm256];
    }
    return cost >> 8;
}