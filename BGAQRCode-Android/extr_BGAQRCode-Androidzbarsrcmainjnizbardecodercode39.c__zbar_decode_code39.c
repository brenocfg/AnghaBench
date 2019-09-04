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
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_14__ {unsigned int s9; int character; int element; int width; scalar_t__ direction; } ;
struct TYPE_13__ {int* buf; TYPE_2__ code39; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code39_decoder_t ;

/* Variables and functions */
 int CFG (TYPE_2__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZBAR_BAR ; 
 int /*<<< orphan*/  ZBAR_CFG_MAX_LEN ; 
 int /*<<< orphan*/  ZBAR_CFG_MIN_LEN ; 
 int /*<<< orphan*/  ZBAR_CODE39 ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 int /*<<< orphan*/  ZBAR_PARTIAL ; 
 scalar_t__ acquire_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_width (int,unsigned int) ; 
 char code39_decode9 (TYPE_1__*) ; 
 int /*<<< orphan*/  code39_decode_start (TYPE_1__*) ; 
 int /*<<< orphan*/  code39_postprocess (TYPE_1__*) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 scalar_t__ get_color (TYPE_1__*) ; 
 unsigned int get_width (TYPE_1__*,int) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zassert (int,int /*<<< orphan*/ ,char*,char,unsigned int) ; 

zbar_symbol_type_t _zbar_decode_code39 (zbar_decoder_t *dcode)
{
    code39_decoder_t *dcode39 = &dcode->code39;

    /* update latest character width */
    dcode39->s9 -= get_width(dcode, 9);
    dcode39->s9 += get_width(dcode, 0);

    if(dcode39->character < 0) {
        if(get_color(dcode) != ZBAR_BAR)
            return(ZBAR_NONE);
        dbprintf(2, "      code39:");
        return(code39_decode_start(dcode));
    }

    if(++dcode39->element < 9)
        return(ZBAR_NONE);

    dbprintf(2, "      code39[%c%02d+%x]",
             (dcode39->direction) ? '<' : '>',
             dcode39->character, dcode39->element);

    if(dcode39->element == 10) {
        unsigned space = get_width(dcode, 0);
        if(dcode39->character &&
           dcode->buf[dcode39->character - 1] == 0x2b) {  /* STOP */
            /* trim STOP character */
            dcode39->character--;
            zbar_symbol_type_t sym = ZBAR_NONE;

            /* trailing quiet zone check */
            if(space && space < dcode39->width / 2)
                dbprintf(2, " [invalid qz]\n");
            else if(dcode39->character < CFG(*dcode39, ZBAR_CFG_MIN_LEN) ||
                    (CFG(*dcode39, ZBAR_CFG_MAX_LEN) > 0 &&
                     dcode39->character > CFG(*dcode39, ZBAR_CFG_MAX_LEN)))
                dbprintf(2, " [invalid len]\n");
            else if(!code39_postprocess(dcode)) {
                /* FIXME checksum */
                dbprintf(2, " [valid end]\n");
                sym = ZBAR_CODE39;
            }
            dcode39->character = -1;
            if(!sym)
                release_lock(dcode, ZBAR_CODE39);
            return(sym);
        }
        if(space > dcode39->width / 2) {
            /* inter-character space check failure */
            dbprintf(2, " ics>%d [invalid ics]", dcode39->width);
            if(dcode39->character)
                release_lock(dcode, ZBAR_CODE39);
            dcode39->character = -1;
        }
        dcode39->element = 0;
        dbprintf(2, "\n");
        return(ZBAR_NONE);
    }

    dbprintf(2, " s=%d ", dcode39->s9);
    if(!check_width(dcode39->width, dcode39->s9)) {
        dbprintf(2, " [width]\n");
        if(dcode39->character)
            release_lock(dcode, ZBAR_CODE39);
        dcode39->character = -1;
        return(ZBAR_NONE);
    }

    signed char c = code39_decode9(dcode);
    dbprintf(2, " c=%d", c);

    /* lock shared resources */
    if(!dcode39->character && acquire_lock(dcode, ZBAR_CODE39)) {
        dcode39->character = -1;
        return(ZBAR_PARTIAL);
    }

    if(c < 0 || size_buf(dcode, dcode39->character + 1)) {
        dbprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
        release_lock(dcode, ZBAR_CODE39);
        dcode39->character = -1;
        return(ZBAR_NONE);
    }
    else {
        zassert(c < 0x2c, ZBAR_NONE, "c=%02x s9=%x\n", c, dcode39->s9);
        dbprintf(2, "\n");
    }

    dcode->buf[dcode39->character++] = c;

    return(ZBAR_NONE);
}