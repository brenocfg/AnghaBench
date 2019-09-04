#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_12__ {int character; int element; int direction; unsigned char* buf; int /*<<< orphan*/  s10; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {unsigned char* buf; TYPE_2__ i25; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ i25_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZBAR_I25 ; 
 int /*<<< orphan*/  ZBAR_NONE ; 
 int /*<<< orphan*/  ZBAR_PARTIAL ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 scalar_t__ get_width (TYPE_1__*,int) ; 
 scalar_t__ i25_acquire_lock (TYPE_1__*) ; 
 unsigned char i25_decode10 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  i25_decode_end (TYPE_1__*) ; 
 int /*<<< orphan*/  i25_decode_start (TYPE_1__*) ; 
 int /*<<< orphan*/  release_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ size_buf (TYPE_1__*,int) ; 

zbar_symbol_type_t _zbar_decode_i25 (zbar_decoder_t *dcode)
{
    i25_decoder_t *dcode25 = &dcode->i25;

    /* update latest character width */
    dcode25->s10 -= get_width(dcode, 10);
    dcode25->s10 += get_width(dcode, 0);

    if(dcode25->character < 0 &&
       !i25_decode_start(dcode))
        return(ZBAR_NONE);

    if(--dcode25->element == 6 - dcode25->direction)
        return(i25_decode_end(dcode));
    else if(dcode25->element)
        return(ZBAR_NONE);

    /* FIXME check current character width against previous */
    dcode25->width = dcode25->s10;

    dbprintf(2, "      i25[%c%02d+%x]",
             (dcode25->direction) ? '<' : '>',
             dcode25->character, dcode25->element);

    if(dcode25->character == 4 && i25_acquire_lock(dcode))
        return(ZBAR_PARTIAL);

    unsigned char c = i25_decode10(dcode, 1);
    dbprintf(2, " c=%x", c);
    if(c > 9) {
        dbprintf(2, " [aborted]\n");
        goto reset;
    }

    if(size_buf(dcode, dcode25->character + 3)) {
        dbprintf(2, " [overflow]\n");
        goto reset;
    }

    unsigned char *buf;
    if(dcode25->character >= 4)
        buf = dcode->buf;
    else
        buf = dcode25->buf;
    buf[dcode25->character++] = c + '0';

    c = i25_decode10(dcode, 0);
    dbprintf(2, " c=%x", c);
    if(c > 9) {
        dbprintf(2, " [aborted]\n");
        goto reset;
    }
    else
        dbprintf(2, "\n");

    buf[dcode25->character++] = c + '0';
    dcode25->element = 10;
    return((dcode25->character == 2) ? ZBAR_PARTIAL : ZBAR_NONE);

reset:
    if(dcode25->character >= 4)
        release_lock(dcode, ZBAR_I25);
    dcode25->character = -1;
    return(ZBAR_NONE);
}