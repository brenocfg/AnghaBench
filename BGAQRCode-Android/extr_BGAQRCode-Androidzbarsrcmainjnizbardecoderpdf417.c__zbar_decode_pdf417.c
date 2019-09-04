#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_11__ {int character; int direction; scalar_t__ element; int /*<<< orphan*/  s8; } ;
struct TYPE_10__ {int direction; scalar_t__ modifiers; int /*<<< orphan*/  buf; TYPE_2__ pdf417; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ pdf417_decoder_t ;

/* Variables and functions */
 short PDF417_STOP ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 int /*<<< orphan*/  ZBAR_PDF417 ; 
 int /*<<< orphan*/  _zbar_decoder_buf_dump (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int get_color (TYPE_1__*) ; 
 scalar_t__ get_width (TYPE_1__*,int) ; 
 short pdf417_decode8 (TYPE_1__*) ; 
 int /*<<< orphan*/  pdf417_decode_start (TYPE_1__*) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zassert (int,int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 

zbar_symbol_type_t _zbar_decode_pdf417 (zbar_decoder_t *dcode)
{
    pdf417_decoder_t *dcode417 = &dcode->pdf417;

    /* update latest character width */
    dcode417->s8 -= get_width(dcode, 8);
    dcode417->s8 += get_width(dcode, 0);

    if(dcode417->character < 0) {
        pdf417_decode_start(dcode);
        dbprintf(4, "\n");
        return(0);
    }

    /* process every 8th element of active symbol */
    if(++dcode417->element)
        return(0);
    dcode417->element = 0;

    dbprintf(2, "      pdf417[%c%02d]:",
             (dcode417->direction) ? '<' : '>', dcode417->character);

    if(get_color(dcode) != dcode417->direction) {
        int c = dcode417->character;
        release_lock(dcode, ZBAR_PDF417);
        dcode417->character = -1;
        zassert(get_color(dcode) == dcode417->direction, ZBAR_NONE,
                "color=%x dir=%x char=%d elem=0 %s\n",
                get_color(dcode), dcode417->direction, c,
                _zbar_decoder_buf_dump(dcode->buf, c));
    }

    signed short c = pdf417_decode8(dcode);
    if(c < 0 || size_buf(dcode, dcode417->character + 1)) {
        dbprintf(1, (c < 0) ? " [aborted]\n" : " [overflow]\n");
        release_lock(dcode, ZBAR_PDF417);
        dcode417->character = -1;
        return(0);
    }

    /* FIXME TBD infer dimensions, save codewords */

    if(c == PDF417_STOP) {
        dbprintf(1, " [valid stop]");
        /* FIXME check trailing bar and qz */
        dcode->direction = 1 - 2 * dcode417->direction;
        dcode->modifiers = 0;
        release_lock(dcode, ZBAR_PDF417);
        dcode417->character = -1;
    }

    dbprintf(2, "\n");
    return(0);
}