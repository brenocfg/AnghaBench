#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int s10; int element; scalar_t__ character; scalar_t__ direction; } ;
struct TYPE_6__ {TYPE_2__ i25; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ i25_decoder_t ;

/* Variables and functions */
 scalar_t__ ZBAR_BAR ; 
 char ZBAR_NONE ; 
 char ZBAR_PARTIAL ; 
 int /*<<< orphan*/  dbprintf (int,char*,int,unsigned char,...) ; 
 scalar_t__ get_color (TYPE_1__*) ; 
 unsigned int get_width (TYPE_1__*,unsigned char) ; 
 unsigned char i25_decode1 (unsigned char,unsigned int,int) ; 

__attribute__((used)) static inline signed char i25_decode_start (zbar_decoder_t *dcode)
{
    i25_decoder_t *dcode25 = &dcode->i25;
    if(dcode25->s10 < 10)
        return(ZBAR_NONE);

    unsigned char enc = 0;
    unsigned char i = 10;
    enc = i25_decode1(enc, get_width(dcode, i++), dcode25->s10);
    enc = i25_decode1(enc, get_width(dcode, i++), dcode25->s10);
    enc = i25_decode1(enc, get_width(dcode, i++), dcode25->s10);

    if((get_color(dcode) == ZBAR_BAR)
       ? enc != 4
       : (enc = i25_decode1(enc, get_width(dcode, i++), dcode25->s10))) {
        dbprintf(4, "      i25: s=%d enc=%x [invalid]\n", dcode25->s10, enc);
        return(ZBAR_NONE);
    }

    /* check leading quiet zone - spec is 10n(?)
     * we require 5.25n for w=2n to 6.75n for w=3n
     * (FIXME should really factor in w:n ratio)
     */
    unsigned quiet = get_width(dcode, i);
    if(quiet && quiet < dcode25->s10 * 3 / 8) {
        dbprintf(3, "      i25: s=%d enc=%x q=%d [invalid qz]\n",
                 dcode25->s10, enc, quiet);
        return(ZBAR_NONE);
    }

    dcode25->direction = get_color(dcode);
    dcode25->element = 1;
    dcode25->character = 0;
    return(ZBAR_PARTIAL);
}