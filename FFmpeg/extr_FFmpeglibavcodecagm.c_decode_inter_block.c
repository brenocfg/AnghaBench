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
struct TYPE_5__ {int* block; int flags; TYPE_1__ scantable; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AGMContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int read_code (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

__attribute__((used)) static int decode_inter_block(AGMContext *s, GetBitContext *gb,
                              const int *quant_matrix, int *skip,
                              int *map)
{
    const uint8_t *scantable = s->scantable.permutated;
    int16_t *block = s->block;
    int level, ret;

    memset(block, 0, sizeof(s->block));

    for (int i = 0; i < 64;) {
        if (*skip > 0) {
            int rskip;

            rskip = FFMIN(*skip, 64 - i);
            i += rskip;
            *skip -= rskip;
        } else {
            ret = read_code(gb, skip, &level, map, s->flags & 1);
            if (ret < 0)
                return ret;

            block[scantable[i]] = level * quant_matrix[i];
            i++;
        }
    }

    return 0;
}