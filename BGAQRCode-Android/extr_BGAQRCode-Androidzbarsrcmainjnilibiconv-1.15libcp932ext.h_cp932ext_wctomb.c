#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;
struct TYPE_16__ {unsigned short used; unsigned short indx; } ;
typedef  TYPE_1__ Summary16 ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 unsigned short* cp932ext_2charset ; 
 TYPE_1__* cp932ext_uni2indx_page21 ; 
 TYPE_1__* cp932ext_uni2indx_page24 ; 
 TYPE_1__* cp932ext_uni2indx_page30 ; 
 TYPE_1__* cp932ext_uni2indx_page32 ; 
 TYPE_1__* cp932ext_uni2indx_page4e ; 
 TYPE_1__* cp932ext_uni2indx_page57 ; 
 TYPE_1__* cp932ext_uni2indx_page5b ; 
 TYPE_1__* cp932ext_uni2indx_page5f ; 
 TYPE_1__* cp932ext_uni2indx_page7d ; 
 TYPE_1__* cp932ext_uni2indx_page83 ; 
 TYPE_1__* cp932ext_uni2indx_page88 ; 
 TYPE_1__* cp932ext_uni2indx_page90 ; 
 TYPE_1__* cp932ext_uni2indx_pagef9 ; 
 TYPE_1__* cp932ext_uni2indx_pageff ; 

__attribute__((used)) static int
cp932ext_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 2) {
    const Summary16 *summary = NULL;
    if (wc >= 0x2100 && wc < 0x22c0)
      summary = &cp932ext_uni2indx_page21[(wc>>4)-0x210];
    else if (wc >= 0x2400 && wc < 0x2480)
      summary = &cp932ext_uni2indx_page24[(wc>>4)-0x240];
    else if (wc >= 0x3000 && wc < 0x3020)
      summary = &cp932ext_uni2indx_page30[(wc>>4)-0x300];
    else if (wc >= 0x3200 && wc < 0x33d0)
      summary = &cp932ext_uni2indx_page32[(wc>>4)-0x320];
    else if (wc >= 0x4e00 && wc < 0x5590)
      summary = &cp932ext_uni2indx_page4e[(wc>>4)-0x4e0];
    else if (wc >= 0x5700 && wc < 0x59c0)
      summary = &cp932ext_uni2indx_page57[(wc>>4)-0x570];
    else if (wc >= 0x5b00 && wc < 0x5de0)
      summary = &cp932ext_uni2indx_page5b[(wc>>4)-0x5b0];
    else if (wc >= 0x5f00 && wc < 0x7ba0)
      summary = &cp932ext_uni2indx_page5f[(wc>>4)-0x5f0];
    else if (wc >= 0x7d00 && wc < 0x7fb0)
      summary = &cp932ext_uni2indx_page7d[(wc>>4)-0x7d0];
    else if (wc >= 0x8300 && wc < 0x85c0)
      summary = &cp932ext_uni2indx_page83[(wc>>4)-0x830];
    else if (wc >= 0x8800 && wc < 0x8ed0)
      summary = &cp932ext_uni2indx_page88[(wc>>4)-0x880];
    else if (wc >= 0x9000 && wc < 0x9ee0)
      summary = &cp932ext_uni2indx_page90[(wc>>4)-0x900];
    else if (wc >= 0xf900 && wc < 0xfa30)
      summary = &cp932ext_uni2indx_pagef9[(wc>>4)-0xf90];
    else if (wc >= 0xff00 && wc < 0xfff0)
      summary = &cp932ext_uni2indx_pageff[(wc>>4)-0xff0];
    if (summary) {
      unsigned short used = summary->used;
      unsigned int i = wc & 0x0f;
      if (used & ((unsigned short) 1 << i)) {
        unsigned short c;
        /* Keep in 'used' only the bits 0..i-1. */
        used &= ((unsigned short) 1 << i) - 1;
        /* Add 'summary->indx' and the number of bits set in 'used'. */
        used = (used & 0x5555) + ((used & 0xaaaa) >> 1);
        used = (used & 0x3333) + ((used & 0xcccc) >> 2);
        used = (used & 0x0f0f) + ((used & 0xf0f0) >> 4);
        used = (used & 0x00ff) + (used >> 8);
        c = cp932ext_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
        return 2;
      }
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}