#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int s8; scalar_t__ character; scalar_t__ element; scalar_t__ direction; } ;
struct TYPE_7__ {TYPE_2__ pdf417; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ pdf417_decoder_t ;

/* Variables and functions */
 scalar_t__ ZBAR_BAR ; 
 char ZBAR_PARTIAL ; 
 int /*<<< orphan*/  ZBAR_PDF417 ; 
 scalar_t__ ZBAR_SPACE ; 
 scalar_t__ acquire_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 int decode_e (scalar_t__,unsigned int,int) ; 
 scalar_t__ get_color (TYPE_1__*) ; 
 scalar_t__ get_width (TYPE_1__*,int) ; 

__attribute__((used)) static inline signed char pdf417_decode_start(zbar_decoder_t *dcode)
{
    unsigned s = dcode->pdf417.s8;
    if(s < 8)
        return(0);

    int ei = decode_e(get_width(dcode, 0) + get_width(dcode, 1), s, 17);
    int ex = (get_color(dcode) == ZBAR_SPACE) ? 2 : 6;
    if(ei != ex)
        return(0);

    ei = decode_e(get_width(dcode, 1) + get_width(dcode, 2), s, 17);
    if(ei)
        return(0);

    ei = decode_e(get_width(dcode, 2) + get_width(dcode, 3), s, 17);
    ex = (get_color(dcode) == ZBAR_SPACE) ? 0 : 2;
    if(ei != ex)
        return(0);

    ei = decode_e(get_width(dcode, 3) + get_width(dcode, 4), s, 17);
    ex = (get_color(dcode) == ZBAR_SPACE) ? 0 : 2;
    if(ei != ex)
        return(0);

    ei = decode_e(get_width(dcode, 4) + get_width(dcode, 5), s, 17);
    if(ei)
        return(0);

    ei = decode_e(get_width(dcode, 5) + get_width(dcode, 6), s, 17);
    if(ei)
        return(0);

    ei = decode_e(get_width(dcode, 6) + get_width(dcode, 7), s, 17);
    ex = (get_color(dcode) == ZBAR_SPACE) ? 7 : 1;
    if(ei != ex)
        return(0);

    ei = decode_e(get_width(dcode, 7) + get_width(dcode, 8), s, 17);
    ex = (get_color(dcode) == ZBAR_SPACE) ? 8 : 1;

    if(get_color(dcode) == ZBAR_BAR) {
        /* stop character has extra bar */
        if(ei != 1)
            return(0);
        ei = decode_e(get_width(dcode, 8) + get_width(dcode, 9), s, 17);
    }

    dbprintf(2, "      pdf417[%c]: s=%d",
             (get_color(dcode)) ? '<' : '>', s);

    /* check quiet zone */
    if(ei >= 0 && ei < ex) {
        dbprintf(2, " [invalid quiet]\n");
        return(0);
    }

    /* lock shared resources */
    if(acquire_lock(dcode, ZBAR_PDF417)) {
        dbprintf(2, " [locked %d]\n", dcode->lock);
        return(0);
    }

    pdf417_decoder_t *dcode417 = &dcode->pdf417;
    dcode417->direction = get_color(dcode);
    dcode417->element = 0;
    dcode417->character = 0;

    dbprintf(2, " [valid start]\n");
    return(ZBAR_PARTIAL);
}