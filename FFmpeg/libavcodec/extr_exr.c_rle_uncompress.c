#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* reorder_pixels ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* predictor ) (int /*<<< orphan*/ *,int) ;} ;
struct TYPE_8__ {TYPE_1__ dsp; } ;
struct TYPE_7__ {int /*<<< orphan*/ * tmp; int /*<<< orphan*/  uncompressed_data; } ;
typedef  TYPE_2__ EXRThreadData ;
typedef  TYPE_3__ EXRContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rle_uncompress(EXRContext *ctx, const uint8_t *src, int compressed_size,
                          int uncompressed_size, EXRThreadData *td)
{
    uint8_t *d      = td->tmp;
    const int8_t *s = src;
    int ssize       = compressed_size;
    int dsize       = uncompressed_size;
    uint8_t *dend   = d + dsize;
    int count;

    while (ssize > 0) {
        count = *s++;

        if (count < 0) {
            count = -count;

            if ((dsize -= count) < 0 ||
                (ssize -= count + 1) < 0)
                return AVERROR_INVALIDDATA;

            while (count--)
                *d++ = *s++;
        } else {
            count++;

            if ((dsize -= count) < 0 ||
                (ssize -= 2) < 0)
                return AVERROR_INVALIDDATA;

            while (count--)
                *d++ = *s;

            s++;
        }
    }

    if (dend != d)
        return AVERROR_INVALIDDATA;

    av_assert1(uncompressed_size % 2 == 0);

    ctx->dsp.predictor(td->tmp, uncompressed_size);
    ctx->dsp.reorder_pixels(td->uncompressed_data, td->tmp, uncompressed_size);

    return 0;
}