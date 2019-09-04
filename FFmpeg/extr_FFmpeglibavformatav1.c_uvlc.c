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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void uvlc(GetBitContext *gb)
{
    int leading_zeros = 0;

    while (get_bits_left(gb)) {
        if (get_bits1(gb))
            break;
        leading_zeros++;
    }

    if (leading_zeros >= 32)
        return;

    skip_bits_long(gb, leading_zeros);
}