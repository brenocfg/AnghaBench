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
struct TYPE_8__ {unsigned int s7; int direction; int /*<<< orphan*/  width; } ;
struct TYPE_7__ {TYPE_2__ codabar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ codabar_decoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  check_width (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned char* codabar_hi ; 
 int* codabar_lo ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 unsigned int decode_sort3 (TYPE_1__*,int) ; 
 unsigned int decode_sortn (TYPE_1__*,int,int) ; 
 unsigned int get_width (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  zassert (int,int,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline signed char
codabar_decode7 (zbar_decoder_t *dcode)
{
    codabar_decoder_t *codabar = &dcode->codabar;
    unsigned s = codabar->s7;
    dbprintf(2, " s=%d", s);
    if(s < 7)
        return(-1);

    /* check width */
    if(!check_width(codabar->width, s)) {
        dbprintf(2, " [width]");
        return(-1);
    }

    /* extract min/max bar */
    unsigned ibar = decode_sortn(dcode, 4, 1);
    dbprintf(2, " bar=%04x", ibar);

    unsigned wbmax = get_width(dcode, ibar & 0xf);
    unsigned wbmin = get_width(dcode, ibar >> 12);
    if(8 * wbmin < wbmax ||
       3 * wbmin > 2 * wbmax)
    {
        dbprintf(2, " [bar outer ratio]");
        return(-1);
    }

    unsigned wb1 = get_width(dcode, (ibar >> 8) & 0xf);
    unsigned wb2 = get_width(dcode, (ibar >> 4) & 0xf);
    unsigned long b0b3 = wbmin * wbmax;
    unsigned long b1b2 = wb1 * wb2;
    if(b1b2 + b1b2 / 8 < b0b3) {
        /* single wide bar combinations */
        if(8 * wbmin < 5 * wb1 ||
           8 * wb1 < 5 * wb2 ||
           4 * wb2 > 3 * wbmax ||
           wb2 * wb2 >= wb1 * wbmax)
        {
            dbprintf(2, " [1bar inner ratios]");
            return(-1);
        }
        ibar = (ibar >> 1) & 0x3;
    }
    else if(b1b2 > b0b3 + b0b3 / 8) {
        /* three wide bars, no wide spaces */
        if(4 * wbmin > 3 * wb1 ||
           8 * wb1 < 5 * wb2 ||
           8 * wb2 < 5 * wbmax ||
           wbmin * wb2 >= wb1 * wb1)
        {
            dbprintf(2, " [3bar inner ratios]");
            return(-1);
        }
        ibar = (ibar >> 13) + 4;
    }
    else {
        dbprintf(2, " [bar inner ratios]");
        return(-1);
    }

    unsigned ispc = decode_sort3(dcode, 2);
    dbprintf(2, "(%x) spc=%03x", ibar, ispc);

    unsigned wsmax = get_width(dcode, ispc & 0xf);
    unsigned wsmid = get_width(dcode, (ispc >> 4) & 0xf);
    unsigned wsmin = get_width(dcode, (ispc >> 8) & 0xf);
    if(ibar >> 2) {
        /* verify no wide spaces */
        if(8 * wsmin < wsmax ||
           8 * wsmin < 5 * wsmid ||
           8 * wsmid < 5 * wsmax)
        {
            dbprintf(2, " [0space inner ratios]");
            return(-1);
        }
        ibar &= 0x3;
        if(codabar->direction)
            ibar = 3 - ibar;
        int c = (0xfcde >> (ibar << 2)) & 0xf;
        dbprintf(2, " ex[%d]=%x", ibar, c);
        return(c);
    }
    else if(8 * wsmin < wsmax ||
            3 * wsmin > 2 * wsmax)
    {
        dbprintf(2, " [space outer ratio]");
        return(-1);
    }

    unsigned long s0s2 = wsmin * wsmax;
    unsigned long s1s1 = wsmid * wsmid;
    if(s1s1 + s1s1 / 8 < s0s2) {
        /* single wide space */
        if(8 * wsmin < 5 * wsmid ||
           4 * wsmid > 3 * wsmax)
        {
            dbprintf(2, " [1space inner ratios]");
            return(-1);
        }
        ispc = ((ispc & 0xf) >> 1) - 1;
        unsigned ic = (ispc << 2) | ibar;
        if(codabar->direction)
            ic = 11 - ic;
        int c = codabar_lo[ic];
        dbprintf(2, "(%d) lo[%d]=%x", ispc, ic, c);
        return(c);
    }
    else if(s1s1 > s0s2 + s0s2 / 8) {
        /* two wide spaces, check start/stop */
        if(4 * wsmin > 3 * wsmid ||
           8 * wsmid < 5 * wsmax)
        {
            dbprintf(2, " [2space inner ratios]");
            return(-1);
        }
        if((ispc >> 8) == 4) {
            dbprintf(2, " [space comb]");
            return(-1);
        }
        ispc >>= 10;
        dbprintf(2, "(%d)", ispc);
        unsigned ic = ispc * 4 + ibar;
        zassert(ic < 8, -1, "ic=%d ispc=%d ibar=%d", ic, ispc, ibar);
        unsigned char c = codabar_hi[ic];
        if(c >> 2 != codabar->direction) {
            dbprintf(2, " [invalid stop]");
            return(-1);
        }
        c = (c & 0x3) | 0x10;
        dbprintf(2, " hi[%d]=%x", ic, c);
        return(c);
    }
    else {
        dbprintf(2, " [space inner ratios]");
        return(-1);
    }
}