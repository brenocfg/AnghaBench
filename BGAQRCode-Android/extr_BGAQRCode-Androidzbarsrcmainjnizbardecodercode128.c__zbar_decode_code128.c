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
struct TYPE_14__ {int s6; int character; int element; scalar_t__ direction; char start; int width; } ;
struct TYPE_13__ {int buf_alloc; char* buf; TYPE_2__ code128; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code128_decoder_t ;

/* Variables and functions */
 int CFG (TYPE_2__,int /*<<< orphan*/ ) ; 
 char START_A ; 
 char START_C ; 
 char STOP_FWD ; 
 char STOP_REV ; 
 char ZBAR_BAR ; 
 int /*<<< orphan*/  ZBAR_CFG_MAX_LEN ; 
 int /*<<< orphan*/  ZBAR_CFG_MIN_LEN ; 
 int /*<<< orphan*/  ZBAR_CODE128 ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 scalar_t__ ZBAR_SPACE ; 
 int /*<<< orphan*/  _zbar_decoder_buf_dump (char*,int) ; 
 scalar_t__ acquire_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 char decode6 (TYPE_1__*) ; 
 scalar_t__ get_color (TYPE_1__*) ; 
 unsigned int get_width (TYPE_1__*,int) ; 
 scalar_t__ postprocess (TYPE_1__*) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 
 scalar_t__ validate_checksum (TYPE_1__*) ; 
 int /*<<< orphan*/  zassert (int,int /*<<< orphan*/ ,char*,int,int,char,int /*<<< orphan*/ ) ; 

zbar_symbol_type_t _zbar_decode_code128 (zbar_decoder_t *dcode)
{
    code128_decoder_t *dcode128 = &dcode->code128;
    signed char c;

    /* update latest character width */
    dcode128->s6 -= get_width(dcode, 6);
    dcode128->s6 += get_width(dcode, 0);

    if((dcode128->character < 0)
       ? get_color(dcode) != ZBAR_SPACE
       : (/* process every 6th element of active symbol */
          ++dcode128->element != 6 ||
          /* decode color based on direction */
          get_color(dcode) != dcode128->direction))
        return(0);
    dcode128->element = 0;

    dbprintf(2, "      code128[%c%02d+%x]:",
             (dcode128->direction) ? '<' : '>',
             dcode128->character, dcode128->element);

    c = decode6(dcode);
    if(dcode128->character < 0) {
        unsigned qz;
        dbprintf(2, " c=%02x", c);
        if(c < START_A || c > STOP_REV || c == STOP_FWD) {
            dbprintf(2, " [invalid]\n");
            return(0);
        }
        qz = get_width(dcode, 6);
        if(qz && qz < (dcode128->s6 * 3) / 4) {
            dbprintf(2, " [invalid qz %d]\n", qz);
            return(0);
        }
        /* decoded valid start/stop */
        /* initialize state */
        dcode128->character = 1;
        if(c == STOP_REV) {
            dcode128->direction = ZBAR_BAR;
            dcode128->element = 7;
        }
        else
            dcode128->direction = ZBAR_SPACE;
        dcode128->start = c;
        dcode128->width = dcode128->s6;
        dbprintf(2, " dir=%x [valid start]\n", dcode128->direction);
        return(0);
    }
    else if(c < 0 || size_buf(dcode, dcode128->character + 1)) {
        dbprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
        if(dcode128->character > 1)
            release_lock(dcode, ZBAR_CODE128);
        dcode128->character = -1;
        return(0);
    }
    else {
        unsigned dw;
        if(dcode128->width > dcode128->s6)
            dw = dcode128->width - dcode128->s6;
        else
            dw = dcode128->s6 - dcode128->width;
        dw *= 4;
        if(dw > dcode128->width) {
            dbprintf(1, " [width var]\n");
            if(dcode128->character > 1)
                release_lock(dcode, ZBAR_CODE128);
            dcode128->character = -1;
            return(0);
        }
    }
    dcode128->width = dcode128->s6;

    zassert(dcode->buf_alloc > dcode128->character, 0,
            "alloc=%x idx=%x c=%02x %s\n",
            dcode->buf_alloc, dcode128->character, c,
            _zbar_decoder_buf_dump(dcode->buf, dcode->buf_alloc));

    if(dcode128->character == 1) {
        /* lock shared resources */
        if(acquire_lock(dcode, ZBAR_CODE128)) {
            dcode128->character = -1;
            return(0);
        }
        dcode->buf[0] = dcode128->start;
    }

    dcode->buf[dcode128->character++] = c;

    if(dcode128->character > 2 &&
       ((dcode128->direction)
        ? c >= START_A && c <= START_C
        : c == STOP_FWD)) {
        /* FIXME STOP_FWD should check extra bar (and QZ!) */
        zbar_symbol_type_t sym = ZBAR_CODE128;
        if(validate_checksum(dcode) || postprocess(dcode))
            sym = ZBAR_NONE;
        else if(dcode128->character < CFG(*dcode128, ZBAR_CFG_MIN_LEN) ||
                (CFG(*dcode128, ZBAR_CFG_MAX_LEN) > 0 &&
                 dcode128->character > CFG(*dcode128, ZBAR_CFG_MAX_LEN))) {
            dbprintf(2, " [invalid len]\n");
            sym = ZBAR_NONE;
        }
        else
            dbprintf(2, " [valid end]\n");
        dcode128->character = -1;
        if(!sym)
            release_lock(dcode, ZBAR_CODE128);
        return(sym);
    }

    dbprintf(2, "\n");
    return(0);
}