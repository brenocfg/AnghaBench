#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int bitcount; int max; int min; } ;
struct TYPE_7__ {int max_codebook_search; } ;
typedef  TYPE_1__ MLPEncodeContext ;
typedef  TYPE_2__ BestOffset ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFF_OFFSET_MAX ; 
 int /*<<< orphan*/  HUFF_OFFSET_MIN ; 
 int INT_MAX ; 
 int /*<<< orphan*/  codebook_bits_offset (TYPE_1__*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static inline void codebook_bits(MLPEncodeContext *ctx,
                                 unsigned int channel, int codebook,
                                 int offset, int32_t min, int32_t max,
                                 BestOffset *bo, int direction)
{
    int previous_count = INT_MAX;
    int offset_min, offset_max;
    int is_greater = 0;

    offset_min = FFMAX(min, HUFF_OFFSET_MIN);
    offset_max = FFMIN(max, HUFF_OFFSET_MAX);

    for (;;) {
        BestOffset temp_bo;

        codebook_bits_offset(ctx, channel, codebook,
                             min, max, offset,
                             &temp_bo);

        if (temp_bo.bitcount < previous_count) {
            if (temp_bo.bitcount < bo->bitcount)
                *bo = temp_bo;

            is_greater = 0;
        } else if (++is_greater >= ctx->max_codebook_search)
            break;

        previous_count = temp_bo.bitcount;

        if (direction) {
            offset = temp_bo.max + 1;
            if (offset > offset_max)
                break;
        } else {
            offset = temp_bo.min - 1;
            if (offset < offset_min)
                break;
        }
    }
}