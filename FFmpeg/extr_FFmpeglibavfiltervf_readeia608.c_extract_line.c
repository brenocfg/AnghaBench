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
typedef  int /*<<< orphan*/  value ;
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {int width; int** data; int* linesize; int /*<<< orphan*/  metadata; } ;
struct TYPE_6__ {int spw; int min_range; int white; int black; int max_peak_diff; int max_period_diff; scalar_t__ max_start_diff; int bhd; int nb_found; scalar_t__ chp; } ;
typedef  TYPE_1__ ReadEIA608Context ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int FALL ; 
 scalar_t__ FFABS (int) ; 
 int FFMAX (int,int const) ; 
 int FFMIN (int,int const) ; 
 int INT_MAX ; 
 int RISE ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int*,int,char*,int,...) ; 

__attribute__((used)) static void extract_line(AVFilterContext *ctx, AVFilterLink *inlink, AVFrame *in, int line)
{
    ReadEIA608Context *s = ctx->priv;
    int max = 0, min = INT_MAX;
    int i, ch, range = 0;
    const uint8_t *src;
    uint16_t clock[8][2] = { { 0 } };
    const int sync_width = s->spw * in->width;
    int last = 0, peaks = 0, max_peak_diff = 0, dir = RISE;
    const int width_per_bit = (in->width - sync_width) / 19;
    uint8_t byte[2] = { 0 };
    int s1, s2, s3, parity;

    src = &in->data[0][line * in->linesize[0]];
    for (i = 0; i < sync_width; i++) {
        max = FFMAX(max, src[i]);
        min = FFMIN(min, src[i]);
    }

    range = max - min;
    if (range < s->min_range)
        return;

    for (i = 0; i < sync_width; i++) {
        int Y = src[i];

        if (dir == RISE) {
            if (Y < last) {
                dir = FALL;
                if (last >= s->white) {
                    clock[peaks][0] = last;
                    clock[peaks][1] = i;
                    peaks++;
                    if (peaks > 7)
                        break;
                }
            }
        } else if (dir == FALL) {
            if (Y > last && last <= s->black) {
                dir = RISE;
            }
        }
        last = Y;
    }

    if (peaks != 7)
        return;

    for (i = 1; i < 7; i++)
        max_peak_diff = FFMAX(max_peak_diff, FFABS(clock[i][0] - clock[i-1][0]));

    if (max_peak_diff > s->max_peak_diff)
        return;

    max = 0; min = INT_MAX;
    for (i = 1; i < 7; i++) {
        max = FFMAX(max, FFABS(clock[i][1] - clock[i-1][1]));
        min = FFMIN(min, FFABS(clock[i][1] - clock[i-1][1]));
    }

    range = max - min;
    if (range > s->max_period_diff)
        return;

    s1 = src[sync_width + width_per_bit * 0 + width_per_bit / 2];
    s2 = src[sync_width + width_per_bit * 1 + width_per_bit / 2];
    s3 = src[sync_width + width_per_bit * 2 + width_per_bit / 2];

    if (FFABS(s1 - s2) > s->max_start_diff || s1 > s->black || s2 > s->black || s3 < s->white)
        return;

    for (ch = 0; ch < 2; ch++) {
        for (parity = 0, i = 0; i < 8; i++) {
            int b = src[sync_width + width_per_bit * (i + 3 + 8 * ch) + width_per_bit / 2];

            if (b - s1 > (s3 - s1) * s->bhd) {
                b = 1;
                parity++;
            } else {
                b = 0;
            }
            byte[ch] |= b << i;
        }

        if (s->chp) {
            if (!(parity & 1)) {
                byte[ch] = 0;
            }
        }
    }

    {
        uint8_t key[128], value[128];

        snprintf(key, sizeof(key), "lavfi.readeia608.%d.cc", s->nb_found);
        snprintf(value, sizeof(value), "0x%02X%02X", byte[0], byte[1]);
        av_dict_set(&in->metadata, key, value, 0);

        snprintf(key, sizeof(key), "lavfi.readeia608.%d.line", s->nb_found);
        snprintf(value, sizeof(value), "%d", line);
        av_dict_set(&in->metadata, key, value, 0);
    }

    s->nb_found++;
}