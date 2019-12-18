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
struct TYPE_6__ {int /*<<< orphan*/  (* put_pixels_clamped ) (int /*<<< orphan*/ *,scalar_t__,int) ;} ;
struct TYPE_8__ {TYPE_2__* pic; int /*<<< orphan*/ * block; TYPE_1__ idsp; int /*<<< orphan*/  chroma_dc_quant; int /*<<< orphan*/ * left_dc; int /*<<< orphan*/ * top_dc; int /*<<< orphan*/  ac_quant; int /*<<< orphan*/  luma_dc_quant; int /*<<< orphan*/  gb; } ;
struct TYPE_7__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_3__ CLVContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  clv_dct (int /*<<< orphan*/ *) ; 
 scalar_t__ decode_block (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int decode_mb(CLVContext *c, int x, int y)
{
    int i, has_ac[6], off;

    for (i = 0; i < 6; i++)
        has_ac[i] = get_bits1(&c->gb);

    off = x * 16 + y * 16 * c->pic->linesize[0];
    for (i = 0; i < 4; i++) {
        if (decode_block(c, c->block, has_ac[i], c->ac_quant) < 0)
            return AVERROR_INVALIDDATA;
        if (!x && !(i & 1)) {
            c->block[0] += c->top_dc[0];
            c->top_dc[0] = c->block[0];
        } else {
            c->block[0] += c->left_dc[(i & 2) >> 1];
        }
        c->left_dc[(i & 2) >> 1] = c->block[0];
        c->block[0]             *= c->luma_dc_quant;
        clv_dct(c->block);
        if (i == 2)
            off += c->pic->linesize[0] * 8;
        c->idsp.put_pixels_clamped(c->block,
                                   c->pic->data[0] + off + (i & 1) * 8,
                                   c->pic->linesize[0]);
    }

    off = x * 8 + y * 8 * c->pic->linesize[1];
    for (i = 1; i < 3; i++) {
        if (decode_block(c, c->block, has_ac[i + 3], c->ac_quant) < 0)
            return AVERROR_INVALIDDATA;
        if (!x) {
            c->block[0] += c->top_dc[i];
            c->top_dc[i] = c->block[0];
        } else {
            c->block[0] += c->left_dc[i + 1];
        }
        c->left_dc[i + 1] = c->block[0];
        c->block[0]      *= c->chroma_dc_quant;
        clv_dct(c->block);
        c->idsp.put_pixels_clamped(c->block, c->pic->data[i] + off,
                                   c->pic->linesize[i]);
    }

    return 0;
}