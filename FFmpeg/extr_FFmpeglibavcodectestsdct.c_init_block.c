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
typedef  int int16_t ;
typedef  int /*<<< orphan*/  AVLFG ;

/* Variables and functions */
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_ref_fdct (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_block(int16_t block[64], int test, int is_idct, AVLFG *prng, int vals)
{
    int i, j;

    memset(block, 0, 64 * sizeof(*block));

    switch (test) {
    case 0:
        for (i = 0; i < 64; i++)
            block[i] = (av_lfg_get(prng) % (2*vals)) -vals;
        if (is_idct) {
            ff_ref_fdct(block);
            for (i = 0; i < 64; i++)
                block[i] >>= 3;
        }
        break;
    case 1:
        j = av_lfg_get(prng) % 10 + 1;
        for (i = 0; i < j; i++) {
            int idx = av_lfg_get(prng) % 64;
            block[idx] = av_lfg_get(prng) % (2*vals) -vals;
        }
        break;
    case 2:
        block[ 0] = av_lfg_get(prng) % (16*vals) - (8*vals);
        block[63] = (block[0] & 1) ^ 1;
        break;
    }
}