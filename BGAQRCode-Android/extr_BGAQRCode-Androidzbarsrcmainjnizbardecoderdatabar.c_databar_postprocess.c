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
struct TYPE_5__ {int /*<<< orphan*/  config; } ;
struct TYPE_4__ {unsigned char* buf; int buflen; TYPE_2__ databar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ databar_decoder_t ;

/* Variables and functions */
 scalar_t__ TEST_CFG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_CFG_EMIT_CHECK ; 
 unsigned long _zbar_decoder_buf_dump (unsigned char*,int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned long,...) ; 

__attribute__((used)) static inline void
databar_postprocess (zbar_decoder_t *dcode,
                     unsigned d[4])
{
    databar_decoder_t *db = &dcode->databar;
    int i;
    unsigned c, chk = 0;
    unsigned char *buf = dcode->buf;
    *(buf++) = '0';
    *(buf++) = '1';
    buf += 15;
    *--buf = '\0';
    *--buf = '\0';

    dbprintf(2, "\n    d={%d,%d,%d,%d}", d[0], d[1], d[2], d[3]);
    unsigned long r = d[0] * 1597 + d[1];
    d[1] = r / 10000;
    r %= 10000;
    r = r * 2841 + d[2];
    d[2] = r / 10000;
    r %= 10000;
    r = r * 1597 + d[3];
    d[3] = r / 10000;
    dbprintf(2, " r=%ld", r);

    for(i = 4; --i >= 0; ) {
        c = r % 10;
        chk += c;
        if(i & 1)
            chk += c << 1;
        *--buf = c + '0';
        if(i)
            r /= 10;
    }

    dbprintf(2, " d={%d,%d,%d}", d[1], d[2], d[3]);
    r = d[1] * 2841 + d[2];
    d[2] = r / 10000;
    r %= 10000;
    r = r * 1597 + d[3];
    d[3] = r / 10000;
    dbprintf(2, " r=%ld", r);

    for(i = 4; --i >= 0; ) {
        c = r % 10;
        chk += c;
        if(i & 1)
            chk += c << 1;
        *--buf = c + '0';
        if(i)
            r /= 10;
    }

    r = d[2] * 1597 + d[3];
    dbprintf(2, " d={%d,%d} r=%ld", d[2], d[3], r);

    for(i = 5; --i >= 0; ) {
        c = r % 10;
        chk += c;
        if(!(i & 1))
            chk += c << 1;
        *--buf = c + '0';
        if(i)
            r /= 10;
    }

    /* NB linkage flag not supported */
    if(TEST_CFG(db->config, ZBAR_CFG_EMIT_CHECK)) {
        chk %= 10;
        if(chk)
            chk = 10 - chk;
        buf[13] = chk + '0';
        dcode->buflen = buf - dcode->buf + 14;
    }
    else
        dcode->buflen = buf - dcode->buf + 13;

    dbprintf(2, "\n    %s", _zbar_decoder_buf_dump(dcode->buf, 16));
}