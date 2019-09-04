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
struct TYPE_8__ {unsigned int s7; int* buf; int direction; int element; int character; unsigned int width; } ;
struct TYPE_7__ {TYPE_2__ codabar; } ;
typedef  TYPE_1__ zbar_decoder_t ;
typedef  TYPE_2__ codabar_decoder_t ;

/* Variables and functions */
 char ZBAR_NONE ; 
 char ZBAR_PARTIAL ; 
 int* codabar_hi ; 
 int /*<<< orphan*/  dbprintf (int,char*,...) ; 
 unsigned int decode_sort3 (TYPE_1__*,int) ; 
 unsigned int decode_sortn (TYPE_1__*,int,int) ; 
 int get_width (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  zassert (int,char,char*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline signed char
codabar_decode_start (zbar_decoder_t *dcode)
{
    codabar_decoder_t *codabar = &dcode->codabar;
    unsigned s = codabar->s7;
    if(s < 8)
        return(ZBAR_NONE);
    dbprintf(2, "      codabar: s=%d", s);

    /* check leading quiet zone - spec is 10x */
    unsigned qz = get_width(dcode, 8);
    if((qz && qz * 2 < s) ||
       4 * get_width(dcode, 0) > 3 * s)
    {
        dbprintf(2, " [invalid qz/ics]\n");
        return(ZBAR_NONE);
    }

    /* check space ratios first */
    unsigned ispc = decode_sort3(dcode, 2);
    dbprintf(2, " spc=%03x", ispc);
    if((ispc >> 8) == 4) {
        dbprintf(2, " [space comb]\n");
        return(ZBAR_NONE);
    }

    /* require 2 wide and 1 narrow spaces */
    unsigned wsmax = get_width(dcode, ispc & 0xf);
    unsigned wsmin = get_width(dcode, ispc >> 8);
    unsigned wsmid = get_width(dcode, (ispc >> 4) & 0xf);
    if(8 * wsmin < wsmax ||
       3 * wsmin > 2 * wsmax ||
       4 * wsmin > 3 * wsmid ||
       8 * wsmid < 5 * wsmax ||
       wsmid * wsmid <= wsmax * wsmin)
    {
        dbprintf(2, " [space ratio]\n");
        return(ZBAR_NONE);
    }
    ispc >>= 10;
    dbprintf(2, "(%d)", ispc);

    /* check bar ratios */
    unsigned ibar = decode_sortn(dcode, 4, 1);
    dbprintf(2, " bar=%04x", ibar);

    unsigned wbmax = get_width(dcode, ibar & 0xf);
    unsigned wbmin = get_width(dcode, ibar >> 12);
    if(8 * wbmin < wbmax ||
       3 * wbmin > 2 * wbmax)
    {
        dbprintf(2, " [bar outer ratio]\n");
        return(ZBAR_NONE);
    }

    /* require 1 wide & 3 narrow bars */
    unsigned wb1 = get_width(dcode, (ibar >> 8) & 0xf);
    unsigned wb2 = get_width(dcode, (ibar >> 4) & 0xf);
    if(8 * wbmin < 5 * wb1 ||
       8 * wb1 < 5 * wb2 ||
       4 * wb2 > 3 * wbmax ||
       wb1 * wb2 >= wbmin * wbmax ||
       wb2 * wb2 >= wb1 * wbmax)
    {
        dbprintf(2, " [bar inner ratios]\n");
        return(ZBAR_NONE);
    }
    ibar = ((ibar & 0xf) - 1) >> 1;
    dbprintf(2, "(%d)", ibar);

    /* decode combination */
    int ic = ispc * 4 + ibar;
    zassert(ic < 8, ZBAR_NONE, "ic=%d ispc=%d ibar=%d", ic, ispc, ibar);
    int c = codabar_hi[ic];
    codabar->buf[0] = (c & 0x3) | 0x10;

    /* set character direction */
    codabar->direction = c >> 2;

    codabar->element = 4;
    codabar->character = 1;
    codabar->width = codabar->s7;
    dbprintf(1, " start=%c dir=%x [valid start]\n",
             codabar->buf[0] + 0x31, codabar->direction);
    return(ZBAR_PARTIAL);
}