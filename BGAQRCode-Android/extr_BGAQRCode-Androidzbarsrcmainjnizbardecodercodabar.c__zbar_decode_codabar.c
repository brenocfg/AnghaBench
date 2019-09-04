#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zbar_symbol_type_t ;
struct TYPE_14__ {int s7; int character; int element; unsigned char* buf; scalar_t__ direction; } ;
struct TYPE_13__ {unsigned char* buf; TYPE_2__ codabar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ codabar_decoder_t ;

/* Variables and functions */
 int BUFFER_MIN ; 
 unsigned int CFG (TYPE_2__,int /*<<< orphan*/ ) ; 
 int NIBUF ; 
 int /*<<< orphan*/  ZBAR_CFG_MAX_LEN ; 
 int /*<<< orphan*/  ZBAR_CFG_MIN_LEN ; 
 int /*<<< orphan*/  ZBAR_CODABAR ; 
 scalar_t__ ZBAR_NONE ; 
 scalar_t__ ZBAR_PARTIAL ; 
 scalar_t__ ZBAR_SPACE ; 
 scalar_t__ acquire_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char codabar_decode7 (TYPE_1__*) ; 
 scalar_t__ codabar_decode_start (TYPE_1__*) ; 
 scalar_t__ codabar_postprocess (TYPE_1__*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 scalar_t__ get_color (TYPE_1__*) ; 
 int get_width (TYPE_1__*,int) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 

zbar_symbol_type_t
_zbar_decode_codabar (zbar_decoder_t *dcode)
{
    codabar_decoder_t *codabar = &dcode->codabar;

    /* update latest character width */
    codabar->s7 -= get_width(dcode, 8);
    codabar->s7 += get_width(dcode, 1);

    if(get_color(dcode) != ZBAR_SPACE)
        return(ZBAR_NONE);
    if(codabar->character < 0)
        return(codabar_decode_start(dcode));
    if(codabar->character < 2 &&
       codabar_decode_start(dcode))
        return(ZBAR_PARTIAL);
    if(--codabar->element)
        return(ZBAR_NONE);
    codabar->element = 4;

    dbprintf(1, "      codabar[%c%02d+%x]",
             (codabar->direction) ? '<' : '>',
             codabar->character, codabar->element);

    signed char c = codabar_decode7(dcode);
    dbprintf(1, " %d", c);
    if(c < 0) {
        dbprintf(1, " [aborted]\n");
        goto reset;
    }

    unsigned char *buf;
    if(codabar->character < NIBUF)
        buf = codabar->buf;
    else {
        if(codabar->character >= BUFFER_MIN &&
           size_buf(dcode, codabar->character + 1))
        {
            dbprintf(1, " [overflow]\n");
            goto reset;
        }
        buf = dcode->buf;
    }
    buf[codabar->character++] = c;

    /* lock shared resources */
    if(codabar->character == NIBUF &&
       acquire_lock(dcode, ZBAR_CODABAR))
    {
        codabar->character = -1;
        return(ZBAR_PARTIAL);
    }

    unsigned s = codabar->s7;
    if(c & 0x10) {
        unsigned qz = get_width(dcode, 0);
        if(qz && qz * 2 < s) {
            dbprintf(2, " [invalid qz]\n");
            goto reset;
        }
        unsigned n = codabar->character;
        if(n < CFG(*codabar, ZBAR_CFG_MIN_LEN) ||
           (CFG(*codabar, ZBAR_CFG_MAX_LEN) > 0 &&
            n > CFG(*codabar, ZBAR_CFG_MAX_LEN)))
        {
            dbprintf(2, " [invalid len]\n");
            goto reset;
        }
        if(codabar->character < NIBUF &&
           acquire_lock(dcode, ZBAR_CODABAR))
        {
            codabar->character = -1;
            return(ZBAR_PARTIAL);
        }
        dbprintf(2, " stop=%c", c + 0x31);

        zbar_symbol_type_t sym = codabar_postprocess(dcode);
        if(sym > ZBAR_PARTIAL)
            dbprintf(2, " [valid stop]");
        else {
            release_lock(dcode, ZBAR_CODABAR);
            codabar->character = -1;
        }
        dbprintf(2, "\n");
        return(sym);
    }
    else if(4 * get_width(dcode, 0) > 3 * s) {
        dbprintf(2, " [ics]\n");
        goto reset;
    }

    dbprintf(2, "\n");
    return(ZBAR_NONE);

reset:
    if(codabar->character >= NIBUF)
        release_lock(dcode, ZBAR_CODABAR);
    codabar->character = -1;
    return(ZBAR_NONE);
}