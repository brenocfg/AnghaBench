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
struct TYPE_5__ {int bpp; int /*<<< orphan*/  padded_bits; TYPE_1__* avctx; int /*<<< orphan*/  video_size; int /*<<< orphan*/  video; } ;
struct TYPE_4__ {int height; int width; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ CDXLVideoContext ;

/* Variables and functions */
 int get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bitplanar2chunky(CDXLVideoContext *c, int linesize, uint8_t *out)
{
    GetBitContext gb;
    int x, y, plane;

    if (init_get_bits8(&gb, c->video, c->video_size) < 0)
        return;
    for (plane = 0; plane < c->bpp; plane++) {
        for (y = 0; y < c->avctx->height; y++) {
            for (x = 0; x < c->avctx->width; x++)
                out[linesize * y + x] |= get_bits1(&gb) << plane;
            skip_bits(&gb, c->padded_bits);
        }
    }
}