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
 size_t get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static inline void decode2x2(GetBitContext *gb, uint8_t *dst, int linesize)
{
    int i, j, v[2];

    switch (get_bits(gb, 2)) {
    case 1:
        v[0] = get_bits(gb, 8);
        for (j = 0; j < 2; j++)
            memset(dst + j * linesize, v[0], 2);
        break;
    case 2:
        v[0] = get_bits(gb, 8);
        v[1] = get_bits(gb, 8);
        for (j = 0; j < 2; j++)
            for (i = 0; i < 2; i++)
                dst[j * linesize + i] = v[get_bits1(gb)];
        break;
    case 3:
        for (j = 0; j < 2; j++)
            for (i = 0; i < 2; i++)
                dst[j * linesize + i] = get_bits(gb, 8);
    }
}