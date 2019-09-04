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
struct TYPE_5__ {unsigned int character; int direction; } ;
struct TYPE_4__ {int direction; unsigned char* buf; unsigned int buf_alloc; unsigned int buflen; scalar_t__ modifiers; TYPE_2__ code93; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code93_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_decoder_buf_dump (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int /*<<< orphan*/  zassert (int,int,char*,unsigned int,...) ; 

__attribute__((used)) static inline int
postprocess (zbar_decoder_t *dcode)
{
    code93_decoder_t *dcode93 = &dcode->code93;
    unsigned i, j, n = dcode93->character;
    static const unsigned char code93_graph[] = "-. $/+%";
    static const unsigned char code93_s2[] =
        "\x1b\x1c\x1d\x1e\x1f;<=>?[\\]^_{|}~\x7f\x00\x40`\x7f\x7f\x7f";

    dbprintf(2, "\n    postproc len=%d", n);
    dcode->direction = 1 - 2 * dcode93->direction;
    if(dcode93->direction) {
        /* reverse buffer */
        dbprintf(2, " (rev)");
        for(i = 0; i < n / 2; i++) {
            unsigned j = n - 1 - i;
            unsigned char d = dcode->buf[i];
            dcode->buf[i] = dcode->buf[j];
            dcode->buf[j] = d;
        }
    }

    n -= 2;
    for(i = 0, j = 0; i < n; ) {
        unsigned char d = dcode->buf[i++];
        if(d < 0xa)
            d = '0' + d;
        else if(d < 0x24)
            d = 'A' + d - 0xa;
        else if(d < 0x2b)
            d = code93_graph[d - 0x24];
        else {
            unsigned shift = d;
            zassert(shift < 0x2f, -1, "%s\n",
                    _zbar_decoder_buf_dump(dcode->buf, dcode93->character));
            d = dcode->buf[i++];
            if(d < 0xa || d >= 0x24)
                return(1);
            d -= 0xa;
            switch(shift)
            {
            case 0x2b: d++; break;
            case 0x2c: d = code93_s2[d]; break;
            case 0x2d: d += 0x21; break;
            case 0x2e: d += 0x61; break;
            default: return(1);
            }
        }
        dcode->buf[j++] = d;
    }

    zassert(j < dcode->buf_alloc, 1,
            "j=%02x %s\n", j,
            _zbar_decoder_buf_dump(dcode->buf, dcode->code93.character));
    dcode->buflen = j;
    dcode->buf[j] = '\0';
    dcode->modifiers = 0;
    return(0);
}