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
struct TYPE_6__ {int s4; } ;
struct TYPE_7__ {TYPE_1__ ean; } ;
typedef  TYPE_2__ zbar_decoder_t ;

/* Variables and functions */
 char STATE_ADDON ; 
 scalar_t__ ZBAR_BAR ; 
 int /*<<< orphan*/  dbprintf (int,char*) ; 
 char decode_e (unsigned int,int,int) ; 
 scalar_t__ get_color (TYPE_2__*) ; 
 unsigned int get_width (TYPE_2__*,int) ; 

__attribute__((used)) static inline signed char aux_start (zbar_decoder_t *dcode)
{
    /* FIXME NB add-on has no guard in reverse */
    unsigned e1, e2 = get_width(dcode, 5) + get_width(dcode, 6);
    unsigned char E1;
    if(dcode->ean.s4 < 6)
        return(-1);

    if(decode_e(e2, dcode->ean.s4, 7)) {
        dbprintf(2, " [invalid any]");
        return(-1);
    }

    e1 = get_width(dcode, 4) + get_width(dcode, 5);
    E1 = decode_e(e1, dcode->ean.s4, 7);

    if(get_color(dcode) == ZBAR_BAR) {
        /* check for quiet-zone */
        unsigned qz = get_width(dcode, 7);
        if(!qz || qz > dcode->ean.s4 * 3 / 4) {
            if(!E1) {
                dbprintf(2, " [valid normal]");
                return(0); /* normal symbol start */
            }
            else if(E1 == 1) {
                dbprintf(2, " [valid add-on]");
                return(STATE_ADDON); /* add-on symbol start */
            }
        }
        dbprintf(2, " [invalid start]");
        return(-1);
    }

    if(!E1) {
        /* attempting decode from SPACE => validate center guard */
        unsigned e3 = get_width(dcode, 6) + get_width(dcode, 7);
        unsigned e4 = get_width(dcode, 7) + get_width(dcode, 8);
        if(!decode_e(e3, dcode->ean.s4, 7) &&
           !decode_e(e4, dcode->ean.s4, 7)) {
            dbprintf(2, " [valid center]");
            return(0); /* start after center guard */
        }
    }
    dbprintf(2, " [invalid center]");
    return(-1);
}