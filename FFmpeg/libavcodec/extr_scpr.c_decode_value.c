#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_3__ {int (* get_freq ) (int /*<<< orphan*/ *,size_t,size_t*) ;int (* decode ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,size_t) ;int /*<<< orphan*/  rc; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ SCPRContext ;
typedef  int /*<<< orphan*/  RangeCoder ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 size_t BOT ; 
 int stub1 (int /*<<< orphan*/ *,size_t,size_t*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,size_t,size_t) ; 

__attribute__((used)) static int decode_value(SCPRContext *s, uint32_t *cnt, uint32_t maxc, uint32_t step, uint32_t *rval)
{
    GetByteContext *gb = &s->gb;
    RangeCoder *rc = &s->rc;
    uint32_t totfr = cnt[maxc];
    uint32_t value;
    uint32_t c = 0, cumfr = 0, cnt_c = 0;
    int i, ret;

    if ((ret = s->get_freq(rc, totfr, &value)) < 0)
        return ret;

    while (c < maxc) {
        cnt_c = cnt[c];
        if (value >= cumfr + cnt_c)
            cumfr += cnt_c;
        else
            break;
        c++;
    }

    if (c >= maxc)
        return AVERROR_INVALIDDATA;

    if ((ret = s->decode(gb, rc, cumfr, cnt_c, totfr)) < 0)
        return ret;

    cnt[c] = cnt_c + step;
    totfr += step;
    if (totfr > BOT) {
        totfr = 0;
        for (i = 0; i < maxc; i++) {
            uint32_t nc = (cnt[i] >> 1) + 1;
            cnt[i] = nc;
            totfr += nc;
        }
    }

    cnt[maxc] = totfr;
    *rval = c;

    return 0;
}