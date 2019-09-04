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
struct TYPE_6__ {int character; int direction; } ;
struct TYPE_5__ {int direction; unsigned char* buf; unsigned int buf_alloc; unsigned int buflen; TYPE_2__ code128; int /*<<< orphan*/  modifiers; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code128_decoder_t ;

/* Variables and functions */
 unsigned char CODE_A ; 
 unsigned char CODE_C ; 
 unsigned char FNC1 ; 
 unsigned char FNC2 ; 
 unsigned char FNC3 ; 
 int /*<<< orphan*/  MOD (int /*<<< orphan*/ ) ; 
 unsigned char SHIFT ; 
 unsigned char START_A ; 
 unsigned char START_C ; 
 unsigned char STOP_FWD ; 
 unsigned char STOP_REV ; 
 int /*<<< orphan*/  ZBAR_MOD_AIM ; 
 int /*<<< orphan*/  ZBAR_MOD_GS1 ; 
 int /*<<< orphan*/  _zbar_decoder_buf_dump (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int postprocess_c (TYPE_1__*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  zassert (int,int,char*,unsigned int,...) ; 

__attribute__((used)) static inline unsigned char postprocess (zbar_decoder_t *dcode)
{
    unsigned i, j, cexp;
    unsigned char code = 0, charset;
    code128_decoder_t *dcode128 = &dcode->code128;
    dbprintf(2, "\n    postproc len=%d", dcode128->character);
    dcode->modifiers = 0;
    dcode->direction = 1 - 2 * dcode128->direction;
    if(dcode128->direction) {
        /* reverse buffer */
        dbprintf(2, " (rev)");
        for(i = 0; i < dcode128->character / 2; i++) {
            unsigned j = dcode128->character - 1 - i;
            code = dcode->buf[i];
            dcode->buf[i] = dcode->buf[j];
            dcode->buf[j] = code;
        }
        zassert(dcode->buf[dcode128->character - 1] == STOP_REV, 1,
                "dir=%x %s\n", dcode128->direction,
                _zbar_decoder_buf_dump(dcode->buf, dcode->code128.character));
    }
    else
        zassert(dcode->buf[dcode128->character - 1] == STOP_FWD, 1,
                "dir=%x %s\n", dcode128->direction,
                _zbar_decoder_buf_dump(dcode->buf, dcode->code128.character));

    code = dcode->buf[0];
    zassert(code >= START_A && code <= START_C, 1, "%s\n",
            _zbar_decoder_buf_dump(dcode->buf, dcode->code128.character));

    charset = code - START_A;
    cexp = (code == START_C) ? 1 : 0;
    dbprintf(2, " start=%c", 'A' + charset);

    for(i = 1, j = 0; i < dcode128->character - 2; i++) {
        unsigned char code = dcode->buf[i];
        zassert(!(code & 0x80), 1,
                "i=%x j=%x code=%02x charset=%x cexp=%x %s\n",
                i, j, code, charset, cexp,
                _zbar_decoder_buf_dump(dcode->buf, dcode->code128.character));

        if((charset & 0x2) && (code < 100))
            /* defer character set C for expansion */
            continue;
        else if(code < 0x60) {
            /* convert character set B to ASCII */
            code = code + 0x20;
            if((!charset || (charset == 0x81)) && (code >= 0x60))
                /* convert character set A to ASCII */
                code -= 0x60;
            dcode->buf[j++] = code;
            if(charset & 0x80)
                charset &= 0x7f;
        }
        else {
            dbprintf(2, " %02x", code);
            if(charset & 0x2) {
                unsigned delta;
                /* expand character set C to ASCII */
                zassert(cexp, 1, "i=%x j=%x code=%02x charset=%x cexp=%x %s\n",
                        i, j, code, charset, cexp,
                        _zbar_decoder_buf_dump(dcode->buf,
                                                dcode->code128.character));
                delta = postprocess_c(dcode, cexp, i, j);
                i += delta;
                j += delta * 2;
                cexp = 0;
            }
            if(code < CODE_C) {
                if(code == SHIFT)
                    charset |= 0x80;
                else if(code == FNC2) {
                    /* FIXME FNC2 - message append */
                }
                else if(code == FNC3) {
                    /* FIXME FNC3 - initialize */
                }
            }
            else if(code == FNC1) {
                /* FNC1 - Code 128 subsets or ASCII 0x1d */
                if(i == 1)
                    dcode->modifiers |= MOD(ZBAR_MOD_GS1);
                else if(i == 2)
                    dcode->modifiers |= MOD(ZBAR_MOD_AIM);
                else if(i < dcode->code128.character - 3)
                    dcode->buf[j++] = 0x1d;
                /*else drop trailing FNC1 */
            }
            else if(code >= START_A) {
                dbprintf(1, " [truncated]\n");
                return(1);
            }
            else {
                unsigned char newset = CODE_A - code;
                zassert(code >= CODE_C && code <= CODE_A, 1,
                        "i=%x j=%x code=%02x charset=%x cexp=%x %s\n",
                        i, j, code, charset, cexp,
                        _zbar_decoder_buf_dump(dcode->buf,
                                                dcode->code128.character));
                if(newset != charset)
                    charset = newset;
                else {
                    /* FIXME FNC4 - extended ASCII */
                }
            }
            if(charset & 0x2)
                cexp = i + 1;
        }
    }
    if(charset & 0x2) {
        zassert(cexp, 1, "i=%x j=%x code=%02x charset=%x cexp=%x %s\n",
                i, j, code, charset, cexp,
                _zbar_decoder_buf_dump(dcode->buf,
                                        dcode->code128.character));
        j += postprocess_c(dcode, cexp, i, j) * 2;
    }
    zassert(j < dcode->buf_alloc, 1, "j=%02x %s\n", j,
            _zbar_decoder_buf_dump(dcode->buf, dcode->code128.character));
    dcode->buflen = j;
    dcode->buf[j] = '\0';
    dcode->code128.character = j;
    return(0);
}