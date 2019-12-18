#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int total_freq; int* lookup; int* freq; } ;
struct TYPE_5__ {int (* get_freq ) (int /*<<< orphan*/ *,int,int*) ;int (* decode ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ;int cbits; int /*<<< orphan*/  rc; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ SCPRContext ;
typedef  int /*<<< orphan*/  RangeCoder ;
typedef  TYPE_2__ PixelModel ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int BOT ; 
 int stub1 (int /*<<< orphan*/ *,int,int*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static int decode_unit(SCPRContext *s, PixelModel *pixel, uint32_t step, uint32_t *rval)
{
    GetByteContext *gb = &s->gb;
    RangeCoder *rc = &s->rc;
    uint32_t totfr = pixel->total_freq;
    uint32_t value, x = 0, cumfr = 0, cnt_x = 0;
    int i, j, ret, c, cnt_c;

    if ((ret = s->get_freq(rc, totfr, &value)) < 0)
        return ret;

    while (x < 16) {
        cnt_x = pixel->lookup[x];
        if (value >= cumfr + cnt_x)
            cumfr += cnt_x;
        else
            break;
        x++;
    }

    c = x * 16;
    cnt_c = 0;
    while (c < 256) {
        cnt_c = pixel->freq[c];
        if (value >= cumfr + cnt_c)
            cumfr += cnt_c;
        else
            break;
        c++;
    }
    if (x >= 16 || c >= 256) {
        return AVERROR_INVALIDDATA;
    }

    if ((ret = s->decode(gb, rc, cumfr, cnt_c, totfr)) < 0)
        return ret;

    pixel->freq[c] = cnt_c + step;
    pixel->lookup[x] = cnt_x + step;
    totfr += step;
    if (totfr > BOT) {
        totfr = 0;
        for (i = 0; i < 256; i++) {
            uint32_t nc = (pixel->freq[i] >> 1) + 1;
            pixel->freq[i] = nc;
            totfr += nc;
        }
        for (i = 0; i < 16; i++) {
            uint32_t sum = 0;
            uint32_t i16_17 = i << 4;
            for (j = 0; j < 16; j++)
                sum += pixel->freq[i16_17 + j];
            pixel->lookup[i] = sum;
        }
    }
    pixel->total_freq = totfr;

    *rval = c & s->cbits;

    return 0;
}