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
struct TYPE_14__ {int character; int element; scalar_t__ direction; int buf; int /*<<< orphan*/  width; } ;
struct TYPE_13__ {int* buf; int /*<<< orphan*/  s6; TYPE_2__ code93; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ code93_decoder_t ;

/* Variables and functions */
 scalar_t__ ZBAR_BAR ; 
 int /*<<< orphan*/  ZBAR_CODE93 ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 int /*<<< orphan*/  _zbar_decoder_buf_dump (int*,int) ; 
 scalar_t__ acquire_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_stop (TYPE_1__*) ; 
 scalar_t__ check_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int decode6 (TYPE_1__*) ; 
 int /*<<< orphan*/  decode_abort (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  decode_start (TYPE_1__*) ; 
 scalar_t__ get_color (TYPE_1__*) ; 
 scalar_t__ postprocess (TYPE_1__*) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 
 scalar_t__ validate_checksums (TYPE_1__*) ; 

zbar_symbol_type_t
_zbar_decode_code93 (zbar_decoder_t *dcode)
{
    code93_decoder_t *dcode93 = &dcode->code93;
    int c;

    if(dcode93->character < 0) {
        zbar_symbol_type_t sym;
        if(get_color(dcode) != ZBAR_BAR)
            return(ZBAR_NONE);
        sym = decode_start(dcode);
        dbprintf(2, "\n");
        return(sym);
    }

    if(/* process every 6th element of active symbol */
       ++dcode93->element != 6 ||
       /* decode color based on direction */
       get_color(dcode) == dcode93->direction)
        return(ZBAR_NONE);

    dcode93->element = 0;

    dbprintf(2, "      code93[%c%02d+%x]:",
             (dcode93->direction) ? '<' : '>',
             dcode93->character, dcode93->element);

    if(check_width(dcode->s6, dcode93->width))
        return(decode_abort(dcode, "width var"));

    c = decode6(dcode);
    if(c < 0)
        return(decode_abort(dcode, "aborted"));

    if(c == 0x2f) {
        if(!check_stop(dcode))
            return(ZBAR_NONE);
        if(validate_checksums(dcode))
            return(decode_abort(dcode, "checksum error"));
        if(postprocess(dcode))
            return(decode_abort(dcode, "invalid encoding"));

        dbprintf(2, " [valid end]\n");
        dbprintf(3, "    %s\n",
                 _zbar_decoder_buf_dump(dcode->buf, dcode93->character));

        dcode93->character = -1;
        return(ZBAR_CODE93);
    }

    if(size_buf(dcode, dcode93->character + 1))
        return(decode_abort(dcode, "overflow"));

    dcode93->width = dcode->s6;

    if(dcode93->character == 1) {
        /* lock shared resources */
        if(acquire_lock(dcode, ZBAR_CODE93))
            return(decode_abort(dcode, NULL));
        dcode->buf[0] = dcode93->buf;
    }

    if(!dcode93->character)
        dcode93->buf = c;
    else 
        dcode->buf[dcode93->character] = c;
    dcode93->character++;

    dbprintf(2, "\n");
    return(ZBAR_NONE);
}