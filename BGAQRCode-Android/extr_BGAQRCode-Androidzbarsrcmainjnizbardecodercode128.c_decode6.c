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
struct TYPE_6__ {unsigned int s6; } ;
struct TYPE_7__ {TYPE_1__ code128; } ;
typedef  TYPE_2__ zbar_decoder_t ;

/* Variables and functions */
 scalar_t__ ZBAR_BAR ; 
 char calc_check (char) ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned int,...) ; 
 int decode_e (unsigned int,unsigned int,int) ; 
 char decode_hi (int) ; 
 char decode_lo (int) ; 
 scalar_t__ get_color (TYPE_2__*) ; 
 unsigned int get_width (TYPE_2__*,int) ; 

__attribute__((used)) static inline signed char decode6 (zbar_decoder_t *dcode)
{
    int sig;
    signed char c, chk;
    unsigned bars;

    /* build edge signature of character */
    unsigned s = dcode->code128.s6;

    dbprintf(2, " s=%d", s);
    if(s < 5)
        return(-1);
    /* calculate similar edge measurements */
    sig = (get_color(dcode) == ZBAR_BAR)
        ? ((decode_e(get_width(dcode, 0) + get_width(dcode, 1), s, 11) << 12) |
           (decode_e(get_width(dcode, 1) + get_width(dcode, 2), s, 11) << 8) |
           (decode_e(get_width(dcode, 2) + get_width(dcode, 3), s, 11) << 4) |
           (decode_e(get_width(dcode, 3) + get_width(dcode, 4), s, 11)))
        : ((decode_e(get_width(dcode, 5) + get_width(dcode, 4), s, 11) << 12) |
           (decode_e(get_width(dcode, 4) + get_width(dcode, 3), s, 11) << 8) |
           (decode_e(get_width(dcode, 3) + get_width(dcode, 2), s, 11) << 4) |
           (decode_e(get_width(dcode, 2) + get_width(dcode, 1), s, 11)));
    if(sig < 0)
        return(-1);
    dbprintf(2, " sig=%04x", sig);
    /* lookup edge signature */
    c = (sig & 0x4444) ? decode_hi(sig) : decode_lo(sig);
    if(c == -1)
        return(-1);

    /* character validation */
    bars = (get_color(dcode) == ZBAR_BAR)
        ? (get_width(dcode, 0) + get_width(dcode, 2) + get_width(dcode, 4))
        : (get_width(dcode, 1) + get_width(dcode, 3) + get_width(dcode, 5));
    bars = bars * 11 * 4 / s;
    chk = calc_check(c);
    dbprintf(2, " bars=%d chk=%d", bars, chk);
    if(chk - 7 > bars || bars > chk + 7)
        return(-1);

    return(c & 0x7f);
}