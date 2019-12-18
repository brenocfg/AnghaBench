#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  void* int8_t ;
typedef  void* int16_t ;
struct TYPE_14__ {void* y; void* x; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int flags; struct TYPE_13__** child; void* bias; TYPE_5__ mv; } ;
typedef  TYPE_4__ TileInfo ;
struct TYPE_12__ {int /*<<< orphan*/  bits; scalar_t__ table; } ;
struct TYPE_11__ {int /*<<< orphan*/  bits; scalar_t__ table; } ;
struct TYPE_10__ {int /*<<< orphan*/  bits; scalar_t__ table; } ;
struct TYPE_15__ {int mv_esc; int bias_esc; TYPE_3__ bias_cb; TYPE_2__ mv_cb; TYPE_1__ flags_cb; } ;
typedef  TYPE_5__ MV ;
typedef  TYPE_6__ LevelCodes ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 TYPE_4__* av_calloc (int,int) ; 
 void* get_sbits (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static TileInfo* decode_tile_info(GetBitContext *gb, LevelCodes *lc, int level)
{
    TileInfo *ti;
    int i, flags = 0;
    int16_t bias = 0;
    MV mv = { 0 };

    if (lc[level].flags_cb.table) {
        flags = get_vlc2(gb, lc[level].flags_cb.table, lc[level].flags_cb.bits, 2);
    }

    if (lc[level].mv_cb.table) {
        uint16_t mv_code = get_vlc2(gb, lc[level].mv_cb.table, lc[level].mv_cb.bits, 3);

        if (mv_code != lc[level].mv_esc) {
            mv.x = (int8_t)(mv_code & 0xff);
            mv.y = (int8_t)(mv_code >> 8);
        } else {
            mv.x = get_sbits(gb, 8);
            mv.y = get_sbits(gb, 8);
        }
    }

    if (lc[level].bias_cb.table) {
        uint16_t bias_val = get_vlc2(gb, lc[level].bias_cb.table, lc[level].bias_cb.bits, 2);

        if (bias_val != lc[level].bias_esc) {
            bias = (int16_t)(bias_val);
        } else {
            bias = get_sbits(gb, 16);
        }
    }

    ti = av_calloc(1, sizeof(*ti));
    if (!ti)
        return NULL;

    ti->flags = flags;
    ti->mv = mv;
    ti->bias = bias;

    if (ti->flags) {
        for (i = 0; i < 4; i++) {
            if (ti->flags & (1 << i)) {
                TileInfo *subti = decode_tile_info(gb, lc, level + 1);
                ti->child[i] = subti;
            }
        }
    }

    return ti;
}