#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16_t ;
struct TYPE_4__ {int* permutated; } ;
struct TYPE_5__ {int* block_last_index; TYPE_1__ intra_scantable; scalar_t__** block; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int FFABS (scalar_t__) ; 

__attribute__((used)) static inline void dct_single_coeff_elimination(MpegEncContext *s,
                                                int n, int threshold)
{
    static const char tab[64] = {
        3, 2, 2, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };
    int score = 0;
    int run = 0;
    int i;
    int16_t *block = s->block[n];
    const int last_index = s->block_last_index[n];
    int skip_dc;

    if (threshold < 0) {
        skip_dc = 0;
        threshold = -threshold;
    } else
        skip_dc = 1;

    /* Are all we could set to zero already zero? */
    if (last_index <= skip_dc - 1)
        return;

    for (i = 0; i <= last_index; i++) {
        const int j = s->intra_scantable.permutated[i];
        const int level = FFABS(block[j]);
        if (level == 1) {
            if (skip_dc && i == 0)
                continue;
            score += tab[run];
            run = 0;
        } else if (level > 1) {
            return;
        } else {
            run++;
        }
    }
    if (score >= threshold)
        return;
    for (i = skip_dc; i <= last_index; i++) {
        const int j = s->intra_scantable.permutated[i];
        block[j] = 0;
    }
    if (block[0])
        s->block_last_index[n] = 0;
    else
        s->block_last_index[n] = -1;
}