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
typedef  size_t uint8_t ;
typedef  int int16_t ;
struct TYPE_4__ {size_t* permutated; } ;
struct TYPE_5__ {int* block; int flags; scalar_t__ plus; TYPE_1__ scantable; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AGMContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int read_code (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

__attribute__((used)) static int decode_intra_block(AGMContext *s, GetBitContext *gb,
                              const int *quant_matrix, int *skip, int *dc_level)
{
    const uint8_t *scantable = s->scantable.permutated;
    const int offset = s->plus ? 0 : 1024;
    int16_t *block = s->block;
    int level, ret, map = 0;

    memset(block, 0, sizeof(s->block));

    if (*skip > 0) {
        (*skip)--;
    } else {
        ret = read_code(gb, skip, &level, &map, s->flags & 1);
        if (ret < 0)
            return ret;
        *dc_level += level;
    }
    block[scantable[0]] = offset + *dc_level * quant_matrix[0];

    for (int i = 1; i < 64;) {
        if (*skip > 0) {
            int rskip;

            rskip = FFMIN(*skip, 64 - i);
            i += rskip;
            *skip -= rskip;
        } else {
            ret = read_code(gb, skip, &level, &map, s->flags & 1);
            if (ret < 0)
                return ret;

            block[scantable[i]] = level * quant_matrix[i];
            i++;
        }
    }

    return 0;
}