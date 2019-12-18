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
struct TYPE_5__ {int q_unit_cnt; TYPE_1__* channel; scalar_t__ has_band_ext; int /*<<< orphan*/  has_band_ext_data; } ;
struct TYPE_4__ {int band_ext; void** band_ext_data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  ATRAC9Context ;
typedef  TYPE_1__ ATRAC9ChannelData ;
typedef  TYPE_2__ ATRAC9BlockData ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int** at9_tab_band_ext_cnt ; 
 int** at9_tab_band_ext_group ; 
 int*** at9_tab_band_ext_lengths ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline int parse_band_ext(ATRAC9Context *s, ATRAC9BlockData *b,
                                 GetBitContext *gb, int stereo)
{
    int ext_band = 0;

    if (b->has_band_ext) {
        if (b->q_unit_cnt < 13)
            return AVERROR_INVALIDDATA;
        ext_band = at9_tab_band_ext_group[b->q_unit_cnt - 13][2];
        if (stereo) {
            b->channel[1].band_ext = get_bits(gb, 2);
            b->channel[1].band_ext = ext_band > 2 ? b->channel[1].band_ext : 4;
        } else {
            skip_bits1(gb);
        }
    }

    b->has_band_ext_data = get_bits1(gb);
    if (!b->has_band_ext_data)
        return 0;

    if (!b->has_band_ext) {
        skip_bits(gb, 2);
        skip_bits_long(gb, get_bits(gb, 5));
        return 0;
    }

    b->channel[0].band_ext = get_bits(gb, 2);
    b->channel[0].band_ext = ext_band > 2 ? b->channel[0].band_ext : 4;

    if (!get_bits(gb, 5))
        return 0;

    for (int i = 0; i <= stereo; i++) {
        ATRAC9ChannelData *c = &b->channel[i];
        const int count = at9_tab_band_ext_cnt[c->band_ext][ext_band];
        for (int j = 0; j < count; j++) {
            int len = at9_tab_band_ext_lengths[c->band_ext][ext_band][j];
            c->band_ext_data[j] = get_bits(gb, len);
        }
    }

    return 0;
}