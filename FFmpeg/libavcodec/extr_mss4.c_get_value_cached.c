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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_value_cached(GetBitContext *gb, int vec_pos, uint8_t *vec,
                            int vec_size, int component, int shift, int *prev)
{
    if (vec_pos < vec_size)
        return vec[vec_pos];
    if (!get_bits1(gb))
        return prev[component];
    prev[component] = get_bits(gb, 8 - shift) << shift;
    return prev[component];
}