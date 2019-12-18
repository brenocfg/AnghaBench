#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_10__ {size_t* permutated; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* clear_block ) (int*) ;} ;
struct TYPE_11__ {int* prev_dc; TYPE_4__ scantable; TYPE_3__* ac_vlc; TYPE_2__* dc_vlc; TYPE_1__ bdsp; } ;
struct TYPE_9__ {int /*<<< orphan*/  table; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_5__ JPGContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int* chroma_quant ; 
 size_t* ff_zigzag_direct ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int get_xbits (int /*<<< orphan*/ *,int) ; 
 int* luma_quant ; 
 int /*<<< orphan*/  stub1 (int*) ; 

__attribute__((used)) static int jpg_decode_block(JPGContext *c, GetBitContext *gb,
                            int plane, int16_t *block)
{
    int dc, val, pos;
    const int is_chroma = !!plane;
    const uint8_t *qmat = is_chroma ? chroma_quant : luma_quant;

    if (get_bits_left(gb) < 1)
        return AVERROR_INVALIDDATA;

    c->bdsp.clear_block(block);
    dc = get_vlc2(gb, c->dc_vlc[is_chroma].table, 9, 3);
    if (dc < 0)
        return AVERROR_INVALIDDATA;
    if (dc)
        dc = get_xbits(gb, dc);
    dc                = dc * qmat[0] + c->prev_dc[plane];
    block[0]          = dc;
    c->prev_dc[plane] = dc;

    pos = 0;
    while (pos < 63) {
        val = get_vlc2(gb, c->ac_vlc[is_chroma].table, 9, 3);
        if (val < 0)
            return AVERROR_INVALIDDATA;
        pos += val >> 4;
        val &= 0xF;
        if (pos > 63)
            return val ? AVERROR_INVALIDDATA : 0;
        if (val) {
            int nbits = val;

            val                                 = get_xbits(gb, nbits);
            val                                *= qmat[ff_zigzag_direct[pos]];
            block[c->scantable.permutated[pos]] = val;
        }
    }
    return 0;
}