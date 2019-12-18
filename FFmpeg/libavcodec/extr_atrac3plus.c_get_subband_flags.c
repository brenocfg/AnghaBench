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
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static int get_subband_flags(GetBitContext *gb, uint8_t *out, int num_flags)
{
    int i, result;

    memset(out, 0, num_flags);

    result = get_bits1(gb);
    if (result) {
        if (get_bits1(gb))
            for (i = 0; i < num_flags; i++)
                out[i] = get_bits1(gb);
        else
            memset(out, 1, num_flags);
    }

    return result;
}