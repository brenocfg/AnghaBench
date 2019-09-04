#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;
struct TYPE_10__ {unsigned short used; unsigned short indx; } ;
typedef  TYPE_1__ Summary16 ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 unsigned short* cp950ext_2charset ; 
 TYPE_1__* cp950ext_uni2indx_page25 ; 
 TYPE_1__* cp950ext_uni2indx_page58 ; 
 TYPE_1__* cp950ext_uni2indx_page5a ; 
 TYPE_1__* cp950ext_uni2indx_page60 ; 
 TYPE_1__* cp950ext_uni2indx_page78 ; 
 TYPE_1__* cp950ext_uni2indx_page7c ; 
 TYPE_1__* cp950ext_uni2indx_page88 ; 
 TYPE_1__* cp950ext_uni2indx_page92 ; 

__attribute__((used)) static int
cp950ext_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 2) {
    const Summary16 *summary = NULL;
    if (wc >= 0x2500 && wc < 0x25a0)
      summary = &cp950ext_uni2indx_page25[(wc>>4)-0x250];
    else if (wc >= 0x5800 && wc < 0x58c0)
      summary = &cp950ext_uni2indx_page58[(wc>>4)-0x580];
    else if (wc >= 0x5a00 && wc < 0x5b00)
      summary = &cp950ext_uni2indx_page5a[(wc>>4)-0x5a0];
    else if (wc >= 0x6000 && wc < 0x6060)
      summary = &cp950ext_uni2indx_page60[(wc>>4)-0x600];
    else if (wc >= 0x7800 && wc < 0x7890)
      summary = &cp950ext_uni2indx_page78[(wc>>4)-0x780];
    else if (wc >= 0x7c00 && wc < 0x7cb0)
      summary = &cp950ext_uni2indx_page7c[(wc>>4)-0x7c0];
    else if (wc >= 0x8800 && wc < 0x88d0)
      summary = &cp950ext_uni2indx_page88[(wc>>4)-0x880];
    else if (wc >= 0x9200 && wc < 0x92c0)
      summary = &cp950ext_uni2indx_page92[(wc>>4)-0x920];
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
        c = cp950ext_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
        return 2;
      }
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}