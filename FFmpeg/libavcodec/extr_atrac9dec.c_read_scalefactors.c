#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ VLC ;
struct TYPE_13__ {int band_ext_q_unit; int q_unit_cnt_prev; TYPE_1__* channel; } ;
struct TYPE_12__ {int* scalefactors; int* scalefactors_prev; } ;
struct TYPE_11__ {TYPE_2__** sf_vlc; int /*<<< orphan*/  avctx; } ;
struct TYPE_9__ {int* scalefactors; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ ATRAC9Context ;
typedef  TYPE_4__ ATRAC9ChannelData ;
typedef  TYPE_5__ ATRAC9BlockData ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMIN (int,int const) ; 
 int** at9_tab_sf_weights ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int get_bits (int /*<<< orphan*/ *,int const) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int read_scalefactors(ATRAC9Context *s, ATRAC9BlockData *b,
                                    ATRAC9ChannelData *c, GetBitContext *gb,
                                    int channel_idx, int first_in_pkt)
{
    static const uint8_t mode_map[2][4] = { { 0, 1, 2, 3 }, { 0, 2, 3, 4 } };
    const int mode = mode_map[channel_idx][get_bits(gb, 2)];

    memset(c->scalefactors, 0, sizeof(c->scalefactors));

    if (first_in_pkt && (mode == 4 || ((mode == 3) && !channel_idx))) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid scalefactor coding mode!\n");
        return AVERROR_INVALIDDATA;
    }

    switch (mode) {
    case 0: { /* VLC delta offset */
        const uint8_t *sf_weights = at9_tab_sf_weights[get_bits(gb, 3)];
        const int base = get_bits(gb, 5);
        const int len = get_bits(gb, 2) + 3;
        const VLC *tab = &s->sf_vlc[0][len];

        c->scalefactors[0] = get_bits(gb, len);

        for (int i = 1; i < b->band_ext_q_unit; i++) {
            int val = c->scalefactors[i - 1] + get_vlc2(gb, tab->table, 9, 2);
            c->scalefactors[i] = val & ((1 << len) - 1);
        }

        for (int i = 0; i < b->band_ext_q_unit; i++)
            c->scalefactors[i] += base - sf_weights[i];

        break;
    }
    case 1: { /* CLC offset */
        const int len = get_bits(gb, 2) + 2;
        const int base = len < 5 ? get_bits(gb, 5) : 0;
        for (int i = 0; i < b->band_ext_q_unit; i++)
            c->scalefactors[i] = base + get_bits(gb, len);
        break;
    }
    case 2:
    case 4: { /* VLC dist to baseline */
        const int *baseline = mode == 4 ? c->scalefactors_prev :
                              channel_idx ? b->channel[0].scalefactors :
                              c->scalefactors_prev;
        const int baseline_len = mode == 4 ? b->q_unit_cnt_prev :
                                 channel_idx ? b->band_ext_q_unit :
                                 b->q_unit_cnt_prev;

        const int len = get_bits(gb, 2) + 2;
        const int unit_cnt = FFMIN(b->band_ext_q_unit, baseline_len);
        const VLC *tab = &s->sf_vlc[1][len];

        for (int i = 0; i < unit_cnt; i++) {
            int dist = get_vlc2(gb, tab->table, 9, 2);
            c->scalefactors[i] = baseline[i] + dist;
        }

        for (int i = unit_cnt; i < b->band_ext_q_unit; i++)
            c->scalefactors[i] = get_bits(gb, 5);

        break;
    }
    case 3: { /* VLC offset with baseline */
        const int *baseline = channel_idx ? b->channel[0].scalefactors :
                              c->scalefactors_prev;
        const int baseline_len = channel_idx ? b->band_ext_q_unit :
                                 b->q_unit_cnt_prev;

        const int base = get_bits(gb, 5) - (1 << (5 - 1));
        const int len = get_bits(gb, 2) + 1;
        const int unit_cnt = FFMIN(b->band_ext_q_unit, baseline_len);
        const VLC *tab = &s->sf_vlc[0][len];

        c->scalefactors[0] = get_bits(gb, len);

        for (int i = 1; i < unit_cnt; i++) {
            int val = c->scalefactors[i - 1] + get_vlc2(gb, tab->table, 9, 2);
            c->scalefactors[i] = val & ((1 << len) - 1);
        }

        for (int i = 0; i < unit_cnt; i++)
            c->scalefactors[i] += base + baseline[i];

        for (int i = unit_cnt; i < b->band_ext_q_unit; i++)
            c->scalefactors[i] = get_bits(gb, 5);
        break;
    }
    }

    for (int i = 0; i < b->band_ext_q_unit; i++)
        if (c->scalefactors[i] < 0 || c->scalefactors[i] > 31)
            return AVERROR_INVALIDDATA;

    memcpy(c->scalefactors_prev, c->scalefactors, sizeof(c->scalefactors));

    return 0;
}