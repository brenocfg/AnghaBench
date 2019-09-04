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
 unsigned short* hkscs1999_2charset ; 
 TYPE_1__* hkscs1999_uni2indx_page00 ; 
 TYPE_1__* hkscs1999_uni2indx_page04 ; 
 TYPE_1__* hkscs1999_uni2indx_page1e ; 
 TYPE_1__* hkscs1999_uni2indx_page200 ; 
 TYPE_1__* hkscs1999_uni2indx_page21 ; 
 TYPE_1__* hkscs1999_uni2indx_page23 ; 
 TYPE_1__* hkscs1999_uni2indx_page27 ; 
 TYPE_1__* hkscs1999_uni2indx_page294 ; 
 TYPE_1__* hkscs1999_uni2indx_page297 ; 
 TYPE_1__* hkscs1999_uni2indx_page2e ; 
 TYPE_1__* hkscs1999_uni2indx_page2f8 ; 
 TYPE_1__* hkscs1999_uni2indx_page34 ; 
 TYPE_1__* hkscs1999_uni2indx_pagef9 ; 
 TYPE_1__* hkscs1999_uni2indx_pageff ; 

__attribute__((used)) static int
hkscs1999_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 2) {
    const Summary16 *summary = NULL;
    if (wc >= 0x0000 && wc < 0x02d0)
      summary = &hkscs1999_uni2indx_page00[(wc>>4)];
    else if (wc >= 0x0400 && wc < 0x0460)
      summary = &hkscs1999_uni2indx_page04[(wc>>4)-0x040];
    else if (wc >= 0x1e00 && wc < 0x1ed0)
      summary = &hkscs1999_uni2indx_page1e[(wc>>4)-0x1e0];
    else if (wc >= 0x2100 && wc < 0x21f0)
      summary = &hkscs1999_uni2indx_page21[(wc>>4)-0x210];
    else if (wc >= 0x2300 && wc < 0x2580)
      summary = &hkscs1999_uni2indx_page23[(wc>>4)-0x230];
    else if (wc >= 0x2700 && wc < 0x2740)
      summary = &hkscs1999_uni2indx_page27[(wc>>4)-0x270];
    else if (wc >= 0x2e00 && wc < 0x3240)
      summary = &hkscs1999_uni2indx_page2e[(wc>>4)-0x2e0];
    else if (wc >= 0x3400 && wc < 0x9fc0)
      summary = &hkscs1999_uni2indx_page34[(wc>>4)-0x340];
    else if (wc >= 0xf900 && wc < 0xf910)
      summary = &hkscs1999_uni2indx_pagef9[(wc>>4)-0xf90];
    else if (wc >= 0xff00 && wc < 0xfff0)
      summary = &hkscs1999_uni2indx_pageff[(wc>>4)-0xff0];
    else if (wc >= 0x20000 && wc < 0x291f0)
      summary = &hkscs1999_uni2indx_page200[(wc>>4)-0x2000];
    else if (wc >= 0x29400 && wc < 0x29600)
      summary = &hkscs1999_uni2indx_page294[(wc>>4)-0x2940];
    else if (wc >= 0x29700 && wc < 0x2a6b0)
      summary = &hkscs1999_uni2indx_page297[(wc>>4)-0x2970];
    else if (wc >= 0x2f800 && wc < 0x2f9e0)
      summary = &hkscs1999_uni2indx_page2f8[(wc>>4)-0x2f80];
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
        c = hkscs1999_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
        return 2;
      }
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}