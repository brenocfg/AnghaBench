#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zbar_decoder_t ;

/* Variables and functions */
 unsigned int calc_s (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 char decode_e (unsigned int,unsigned int,int) ; 
 unsigned int get_width (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static inline signed char aux_end (zbar_decoder_t *dcode,
                                   unsigned char fwd)
{
    signed char code, i;

    /* reference width from previous character */
    unsigned s = calc_s(dcode, 4 + fwd, 4);

    /* check quiet zone */
    unsigned qz = get_width(dcode, 0);
    if(!fwd && qz && qz <= s * 3 / 4) {
        dbprintf(2, " [invalid quiet]");
        return(-1);
    }

    dbprintf(2, " (");
    code = 0;
    for(i = 1 - fwd; i < 3 + fwd; i++) {
        unsigned e = get_width(dcode, i) + get_width(dcode, i + 1);
        dbprintf(2, " %d", e);
        code = (code << 2) | decode_e(e, s, 7);
        if(code < 0) {
            dbprintf(2, " [invalid end guard]");
            return(-1);
        }
    }
    dbprintf(2, ") s=%d aux=%x", s, code);
    return(code);
}