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
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_4__ {int* permutated; } ;
struct TYPE_5__ {int* wblocks; int* map; int blocks_w; int flags; int /*<<< orphan*/  map_size; int /*<<< orphan*/  wblocks_size; TYPE_1__ scantable; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AGMContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_code (int /*<<< orphan*/ *,int*,int*,int*,int) ; 

__attribute__((used)) static int decode_inter_blocks(AGMContext *s, GetBitContext *gb,
                               const int *quant_matrix, int *skip,
                               int *map)
{
    const uint8_t *scantable = s->scantable.permutated;
    int level, ret;

    memset(s->wblocks, 0, s->wblocks_size);
    memset(s->map, 0, s->map_size);

    for (int i = 0; i < 64; i++) {
        int16_t *block = s->wblocks + scantable[i];

        for (int j = 0; j < s->blocks_w;) {
            if (*skip > 0) {
                int rskip;

                rskip = FFMIN(*skip, s->blocks_w - j);
                j += rskip;
                block += rskip * 64;
                *skip -= rskip;
            } else {
                ret = read_code(gb, skip, &level, &map[j], s->flags & 1);
                if (ret < 0)
                    return ret;

                block[0] = level * quant_matrix[i];
                block += 64;
                j++;
            }
        }
    }

    return 0;
}