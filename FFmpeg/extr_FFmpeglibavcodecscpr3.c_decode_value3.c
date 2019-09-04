#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int code; } ;
struct TYPE_6__ {TYPE_2__ rc; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ SCPRContext ;
typedef  TYPE_2__ RangeCoder ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  decode3 (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sync_code3 (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int decode_value3(SCPRContext *s, uint32_t max, uint32_t *cntsum,
                         uint16_t *freqs1, uint16_t *freqs2,
                         uint16_t *cnts, uint8_t *dectable,
                         uint32_t *value)
{
    GetByteContext *gb = &s->gb;
    RangeCoder *rc = &s->rc;
    uint32_t r, y, a, b, e, g, q;

    r = dectable[(rc->code & 0xFFFu) >> 7];
    if (r < max) {
        while (freqs2[r + 1] <= (rc->code & 0xFFF)) {
            if (++r >= max)
                break;
        }
    }

    if (r > max)
        return AVERROR_INVALIDDATA;

    cnts[r] += 16;
    a = freqs1[r];
    b = freqs2[r];
    *cntsum += 16;
    if (*cntsum + 16 > 4096) {
        *cntsum = 0;
        for (int c = 0, i = 0; i < max + 1; i++) {
            e = cnts[i];
            freqs2[i] = c;
            freqs1[i] = e;
            g = (c + 127) >> 7;
            c += e;
            q = ((c - 1) >> 7) + 1;
            if (q > g) {
                for (int j = 0; j < q - g; j++)
                    dectable[j + g] = i;
            }
            y = e - (e >> 1);
            cnts[i] = y;
            *cntsum += y;
        }
    }

    decode3(gb, rc, a, b);
    sync_code3(gb, rc);

    *value = r;

    return 0;
}