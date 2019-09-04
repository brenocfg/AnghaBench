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
 unsigned int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits_left (int /*<<< orphan*/ *) ; 
 unsigned int get_unary (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_rice_ook(GetBitContext *gb, int k)
{
    unsigned int x;

    x = get_unary(gb, 1, get_bits_left(gb));

    if (k)
        x = (x << k) | get_bits(gb, k);

    return x;
}