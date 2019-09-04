#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* buf; int buf_alloc; int buflen; } ;
typedef  TYPE_1__ zbar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  FEED_BITS (int) ; 
 unsigned int GS ; 
 int /*<<< orphan*/  PUSH_CHAR (int) ; 
 int /*<<< orphan*/  PUSH_CHAR4 (char,char,char,char) ; 
 int SCH_ALNUM ; 
 int SCH_ISO646 ; 
 int SCH_NUM ; 
 int VAR_MAX (int,int) ; 
 unsigned int _zbar_decoder_buf_dump (unsigned char*,int) ; 
 int /*<<< orphan*/  append_check14 (unsigned char*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int /*<<< orphan*/  decode10 (unsigned char*,int,int) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zassert (int,int,char*,...) ; 

__attribute__((used)) static inline int
databar_postprocess_exp (zbar_decoder_t *dcode,
                         int *data)
{
    int i = 0, enc;
    unsigned n;
    unsigned char *buf;
    unsigned long d = *(data++);
    int len = d / 211 + 4, buflen;

    /* grok encodation method */
    d = *(data++);
    dbprintf(2, "\n    len=%d %03lx", len, d & 0xfff);
    n = (d >> 4) & 0x7f;
    if(n >= 0x40) {
        i = 10;
        enc = 1;
        buflen = 2 + 14 + VAR_MAX(len, 10 - 2 - 44 + 6) + 2;
    }
    else if(n >= 0x38) {
        i = 4;
        enc = 6 + (n & 7);
        buflen = 2 + 14 + 4 + 6 + 2 + 6 + 2;
    }
    else if(n >= 0x30) {
        i = 6;
        enc = 2 + ((n >> 2) & 1);
        buflen = 2 + 14 + 4 + 3 + VAR_MAX(len, 6 - 2 - 44 - 2 - 10) + 2;
    }
    else if(n >= 0x20) {
        i = 7;
        enc = 4 + ((n >> 3) & 1);
        buflen = 2 + 14 + 4 + 6;
    }
    else {
        i = 9;
        enc = 0;
        buflen = VAR_MAX(len, 9 - 2) + 2;
    }
    dbprintf(2, " buflen=%d enc=%d", buflen, enc);
    zassert(buflen > 2, -1, "buflen=%d\n", buflen);

    if(enc < 4) {
        /* grok variable length symbol bit field */
        if((len ^ (d >> (--i))) & 1)
            /* even/odd length mismatch */
            return(-1);
        if(((d >> (--i)) & 1) != (len > 14))
            /* size group mismatch */
            return(-1);
    }
    len -= 2;
    dbprintf(2, " [%d+%d]", i, len);

    if(size_buf(dcode, buflen))
        return(-1);
    buf = dcode->buf;

    /* handle compressed fields */
    if(enc) {
        PUSH_CHAR('0');
        PUSH_CHAR('1');
    }

    if(enc == 1) {
        i -= 4;
        n = (d >> i) & 0xf;
        if(i >= 10)
            return(-1);
        PUSH_CHAR('0' + n);
    }
    else if(enc)
        PUSH_CHAR('9');

    if(enc) {
        int j;
        for(j = 0; j < 4; j++) {
            FEED_BITS(10);
            i -= 10;
            n = (d >> i) & 0x3ff;
            if(n >= 1000)
                return(-1);
            decode10(buf, n, 3);
            buf += 3;
        }
        append_check14(buf - 13);
        buf++;
    }

    switch(enc)
    {
    case 2: /* 01100: AI 392x */
        FEED_BITS(2);
        i -= 2;
        n = (d >> i) & 0x3;
        PUSH_CHAR4('3', '9', '2', '0' + n);
        break;

    case 3: /* 01101: AI 393x */
        FEED_BITS(12);
        i -= 2;
        n = (d >> i) & 0x3;
        PUSH_CHAR4('3', '9', '3', '0' + n);
        i -= 10;
        n = (d >> i) & 0x3ff;
        if(n >= 1000)
            return(-1);
        decode10(buf, n, 3);
        buf += 3;
        break;

    case 4: /* 0100: AI 3103 */
        FEED_BITS(15);
        i -= 15;
        n = (d >> i) & 0x7fff;
        PUSH_CHAR4('3', '1', '0', '3');
        decode10(buf, n, 6);
        buf += 6;
        break;

    case 5: /* 0101: AI 3202/3203 */
        FEED_BITS(15);
        i -= 15;
        n = (d >> i) & 0x7fff;
        dbprintf(2, " v=%d", n);
        PUSH_CHAR4('3', '2', '0', (n >= 10000) ? '3' : '2' );
        if(n >= 10000)
            n -= 10000;
        decode10(buf, n, 6);
        buf += 6;
        break;
    }
    if(enc >= 6) {
        /* 0111000 - 0111111: AI 310x/320x + AI 11/13/15/17 */
        PUSH_CHAR4('3', '1' + (enc & 1), '0', 'x');
        FEED_BITS(20);
        i -= 20;
        n = (d >> i) & 0xfffff;
        dbprintf(2, " [%d+%d] %d", i, len, n);
        if(n >= 1000000)
            return(-1);
        decode10(buf, n, 6);
        *(buf - 1) = *buf;
        *buf = '0';
        buf += 6;

        FEED_BITS(16);
        i -= 16;
        n = (d >> i) & 0xffff;
        if(n < 38400) {
            int dd, mm, yy;
            dd = n % 32;
            n /= 32;
            mm = n % 12 + 1;
            n /= 12;
            yy = n;
            PUSH_CHAR('1');
            PUSH_CHAR('0' + ((enc - 6) | 1));
            decode10(buf, yy, 2);
            buf += 2;
            decode10(buf, mm, 2);
            buf += 2;
            decode10(buf, dd, 2);
            buf += 2;
        }
        else if(n > 38400)
            return(-1);
    }

    if(enc < 4) {
        /* remainder is general-purpose data compaction */
        int scheme = SCH_NUM;
        while(i > 0 || len > 0) {
            FEED_BITS(8);
            dbprintf(2, " [%d+%d]", i, len);

            if(scheme == SCH_NUM) {
                int n1;
                i -= 4;
                if(i < 0)
                    break;
                if(!((d >> i) & 0xf)) {
                    scheme = SCH_ALNUM;
                    dbprintf(2, ">A");
                    continue;
                }
                if(!len && i < 3) {
                    /* special case last digit */
                    n = ((d >> i) & 0xf) - 1;
                    if(n > 9)
                        return(-1);
                    *(buf++) = '0' + n;
                    break;
                }
                i -= 3;
                zassert(i >= 0, -1, "\n");
                n = ((d >> i) & 0x7f) - 8;
                n1 = n % 11;
                n = n / 11;
                dbprintf(2, "N%d%d", n, n1);
                *(buf++) = (n < 10) ? '0' + n : GS;
                *(buf++) = (n1 < 10) ? '0' + n1 : GS;
            }
            else  {
                unsigned c = 0;
                i -= 3;
                if(i < 0)
                    break;
                if(!((d >> i) & 0x7)) {
                    scheme = SCH_NUM;
                    continue;
                }
                i -= 2;
                if(i < 0)
                    break;
                n = (d >> i) & 0x1f;
                if(n == 0x04) {
                    scheme ^= 0x3;
                    dbprintf(2, ">%d", scheme);
                }
                else if(n == 0x0f)
                    c = GS;
                else if(n < 0x0f)
                    c = 43 + n;
                else if(scheme == SCH_ALNUM) {
                    i--;
                    if(i < 0)
                        return(-1);
                    n = (d >> i) & 0x1f;
                    if(n < 0x1a)
                        c = 'A' + n;
                    else if(n == 0x1a)
                        c = '*';
                    else if(n < 0x1f)
                        c = ',' + n - 0x1b;
                    else
                        return(-1);
                }
                else if(scheme == SCH_ISO646 && n < 0x1d) {
                    i -= 2;
                    if(i < 0)
                        return(-1);
                    n = (d >> i) & 0x3f;
                    if(n < 0x1a)
                        c = 'A' + n;
                    else if(n < 0x34)
                        c = 'a' + n - 0x1a;
                    else
                        return(-1);
                }
                else if(scheme == SCH_ISO646) {
                    i -= 3;
                    if(i < 0)
                        return(-1);
                    n = ((d >> i) & 0x1f);
                    dbprintf(2, "(%02x)", n);
                    if(n < 0xa)
                        c = '!' + n - 8;
                    else if(n < 0x15)
                        c = '%' + n - 0xa;
                    else if(n < 0x1b)
                        c = ':' + n - 0x15;
                    else if(n == 0x1b)
                        c = '_';
                    else if(n == 0x1c)
                        c = ' ';
                    else
                        return(-1);
                }
                else
                    return(-1);

                if(c) {
                    dbprintf(2, "%d%c", scheme, c);
                    *(buf++) = c;
                }
            }
        }
        /* FIXME check pad? */
    }

    i = buf - dcode->buf;
    zassert(i < dcode->buf_alloc, -1, "i=%02x %s\n", i,
            _zbar_decoder_buf_dump(dcode->buf, i));

    *buf = 0;
    dcode->buflen = i;
    if(i && *--buf == GS) {
        *buf = 0;
        dcode->buflen--;
    }

    dbprintf(2, "\n    %s", _zbar_decoder_buf_dump(dcode->buf, dcode->buflen));
    return(0);
}