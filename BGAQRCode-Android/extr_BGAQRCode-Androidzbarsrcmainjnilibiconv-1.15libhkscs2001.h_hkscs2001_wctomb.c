#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;
struct TYPE_50__ {unsigned short used; unsigned short indx; } ;
typedef  TYPE_1__ Summary16 ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 unsigned short* hkscs2001_2charset ; 
 TYPE_1__* hkscs2001_uni2indx_page214 ; 
 TYPE_1__* hkscs2001_uni2indx_page219 ; 
 TYPE_1__* hkscs2001_uni2indx_page21d ; 
 TYPE_1__* hkscs2001_uni2indx_page220 ; 
 TYPE_1__* hkscs2001_uni2indx_page227 ; 
 TYPE_1__* hkscs2001_uni2indx_page232 ; 
 TYPE_1__* hkscs2001_uni2indx_page23c ; 
 TYPE_1__* hkscs2001_uni2indx_page241 ; 
 TYPE_1__* hkscs2001_uni2indx_page245 ; 
 TYPE_1__* hkscs2001_uni2indx_page249 ; 
 TYPE_1__* hkscs2001_uni2indx_page251 ; 
 TYPE_1__* hkscs2001_uni2indx_page256 ; 
 TYPE_1__* hkscs2001_uni2indx_page25c ; 
 TYPE_1__* hkscs2001_uni2indx_page26b ; 
 TYPE_1__* hkscs2001_uni2indx_page26d ; 
 TYPE_1__* hkscs2001_uni2indx_page26f ; 
 TYPE_1__* hkscs2001_uni2indx_page271 ; 
 TYPE_1__* hkscs2001_uni2indx_page287 ; 
 TYPE_1__* hkscs2001_uni2indx_page289 ; 
 TYPE_1__* hkscs2001_uni2indx_page28d ; 
 TYPE_1__* hkscs2001_uni2indx_page299 ; 
 TYPE_1__* hkscs2001_uni2indx_page29c ; 
 TYPE_1__* hkscs2001_uni2indx_page2a1 ; 
 TYPE_1__* hkscs2001_uni2indx_page35 ; 
 TYPE_1__* hkscs2001_uni2indx_page3c ; 
 TYPE_1__* hkscs2001_uni2indx_page40 ; 
 TYPE_1__* hkscs2001_uni2indx_page42 ; 
 TYPE_1__* hkscs2001_uni2indx_page4b ; 
 TYPE_1__* hkscs2001_uni2indx_page4e ; 
 TYPE_1__* hkscs2001_uni2indx_page53 ; 
 TYPE_1__* hkscs2001_uni2indx_page57 ; 
 TYPE_1__* hkscs2001_uni2indx_page5a ; 
 TYPE_1__* hkscs2001_uni2indx_page61 ; 
 TYPE_1__* hkscs2001_uni2indx_page65 ; 
 TYPE_1__* hkscs2001_uni2indx_page67 ; 
 TYPE_1__* hkscs2001_uni2indx_page69 ; 
 TYPE_1__* hkscs2001_uni2indx_page6c ; 
 TYPE_1__* hkscs2001_uni2indx_page70 ; 
 TYPE_1__* hkscs2001_uni2indx_page76 ; 
 TYPE_1__* hkscs2001_uni2indx_page7a ; 
 TYPE_1__* hkscs2001_uni2indx_page82 ; 
 TYPE_1__* hkscs2001_uni2indx_page85 ; 
 TYPE_1__* hkscs2001_uni2indx_page88 ; 
 TYPE_1__* hkscs2001_uni2indx_page8b ; 
 TYPE_1__* hkscs2001_uni2indx_page8e ; 
 TYPE_1__* hkscs2001_uni2indx_page91 ; 
 TYPE_1__* hkscs2001_uni2indx_page97 ; 
 TYPE_1__* hkscs2001_uni2indx_page9f ; 

__attribute__((used)) static int
hkscs2001_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 2) {
    const Summary16 *summary = NULL;
    if (wc < 0x9f00) {
      if (wc < 0x6900) {
        if (wc >= 0x3500 && wc < 0x3560)
          summary = &hkscs2001_uni2indx_page35[(wc>>4)-0x350];
        else if (wc >= 0x3c00 && wc < 0x3ee0)
          summary = &hkscs2001_uni2indx_page3c[(wc>>4)-0x3c0];
        else if (wc >= 0x4000 && wc < 0x4080)
          summary = &hkscs2001_uni2indx_page40[(wc>>4)-0x400];
        else if (wc >= 0x4200 && wc < 0x42b0)
          summary = &hkscs2001_uni2indx_page42[(wc>>4)-0x420];
        else if (wc >= 0x4b00 && wc < 0x4c90)
          summary = &hkscs2001_uni2indx_page4b[(wc>>4)-0x4b0];
        else if (wc >= 0x4e00 && wc < 0x51b0)
          summary = &hkscs2001_uni2indx_page4e[(wc>>4)-0x4e0];
        else if (wc >= 0x5300 && wc < 0x5440)
          summary = &hkscs2001_uni2indx_page53[(wc>>4)-0x530];
        else if (wc >= 0x5700 && wc < 0x58e0)
          summary = &hkscs2001_uni2indx_page57[(wc>>4)-0x570];
        else if (wc >= 0x5a00 && wc < 0x5fd0)
          summary = &hkscs2001_uni2indx_page5a[(wc>>4)-0x5a0];
        else if (wc >= 0x6100 && wc < 0x6130)
          summary = &hkscs2001_uni2indx_page61[(wc>>4)-0x610];
        else if (wc >= 0x6500 && wc < 0x6590)
          summary = &hkscs2001_uni2indx_page65[(wc>>4)-0x650];
        else if (wc >= 0x6700 && wc < 0x6770)
          summary = &hkscs2001_uni2indx_page67[(wc>>4)-0x670];
      } else {
        if (wc >= 0x6900 && wc < 0x6a70)
          summary = &hkscs2001_uni2indx_page69[(wc>>4)-0x690];
        else if (wc >= 0x6c00 && wc < 0x6e00)
          summary = &hkscs2001_uni2indx_page6c[(wc>>4)-0x6c0];
        else if (wc >= 0x7000 && wc < 0x74c0)
          summary = &hkscs2001_uni2indx_page70[(wc>>4)-0x700];
        else if (wc >= 0x7600 && wc < 0x78f0)
          summary = &hkscs2001_uni2indx_page76[(wc>>4)-0x760];
        else if (wc >= 0x7a00 && wc < 0x7e70)
          summary = &hkscs2001_uni2indx_page7a[(wc>>4)-0x7a0];
        else if (wc >= 0x8200 && wc < 0x8300)
          summary = &hkscs2001_uni2indx_page82[(wc>>4)-0x820];
        else if (wc >= 0x8500 && wc < 0x8610)
          summary = &hkscs2001_uni2indx_page85[(wc>>4)-0x850];
        else if (wc >= 0x8800 && wc < 0x88a0)
          summary = &hkscs2001_uni2indx_page88[(wc>>4)-0x880];
        else if (wc >= 0x8b00 && wc < 0x8b90)
          summary = &hkscs2001_uni2indx_page8b[(wc>>4)-0x8b0];
        else if (wc >= 0x8e00 && wc < 0x8fd0)
          summary = &hkscs2001_uni2indx_page8e[(wc>>4)-0x8e0];
        else if (wc >= 0x9100 && wc < 0x9400)
          summary = &hkscs2001_uni2indx_page91[(wc>>4)-0x910];
        else if (wc >= 0x9700 && wc < 0x99f0)
          summary = &hkscs2001_uni2indx_page97[(wc>>4)-0x970];
      }
    } else {
      if (wc < 0x25600) {
        if (wc >= 0x9f00 && wc < 0x9fb0)
          summary = &hkscs2001_uni2indx_page9f[(wc>>4)-0x9f0];
        else if (wc >= 0x21400 && wc < 0x21440)
          summary = &hkscs2001_uni2indx_page214[(wc>>4)-0x2140];
        else if (wc >= 0x21900 && wc < 0x21990)
          summary = &hkscs2001_uni2indx_page219[(wc>>4)-0x2190];
        else if (wc >= 0x21d00 && wc < 0x21dc0)
          summary = &hkscs2001_uni2indx_page21d[(wc>>4)-0x21d0];
        else if (wc >= 0x22000 && wc < 0x22080)
          summary = &hkscs2001_uni2indx_page220[(wc>>4)-0x2200];
        else if (wc >= 0x22700 && wc < 0x22720)
          summary = &hkscs2001_uni2indx_page227[(wc>>4)-0x2270];
        else if (wc >= 0x23200 && wc < 0x23400)
          summary = &hkscs2001_uni2indx_page232[(wc>>4)-0x2320];
        else if (wc >= 0x23c00 && wc < 0x23c70)
          summary = &hkscs2001_uni2indx_page23c[(wc>>4)-0x23c0];
        else if (wc >= 0x24100 && wc < 0x24150)
          summary = &hkscs2001_uni2indx_page241[(wc>>4)-0x2410];
        else if (wc >= 0x24500 && wc < 0x24510)
          summary = &hkscs2001_uni2indx_page245[(wc>>4)-0x2450];
        else if (wc >= 0x24900 && wc < 0x24a20)
          summary = &hkscs2001_uni2indx_page249[(wc>>4)-0x2490];
        else if (wc >= 0x25100 && wc < 0x251d0)
          summary = &hkscs2001_uni2indx_page251[(wc>>4)-0x2510];
      } else {
        if (wc >= 0x25600 && wc < 0x256a0)
          summary = &hkscs2001_uni2indx_page256[(wc>>4)-0x2560];
        else if (wc >= 0x25c00 && wc < 0x25d40)
          summary = &hkscs2001_uni2indx_page25c[(wc>>4)-0x25c0];
        else if (wc >= 0x26b00 && wc < 0x26b20)
          summary = &hkscs2001_uni2indx_page26b[(wc>>4)-0x26b0];
        else if (wc >= 0x26d00 && wc < 0x26d80)
          summary = &hkscs2001_uni2indx_page26d[(wc>>4)-0x26d0];
        else if (wc >= 0x26f00 && wc < 0x26fc0)
          summary = &hkscs2001_uni2indx_page26f[(wc>>4)-0x26f0];
        else if (wc >= 0x27100 && wc < 0x27110)
          summary = &hkscs2001_uni2indx_page271[(wc>>4)-0x2710];
        else if (wc >= 0x28700 && wc < 0x28710)
          summary = &hkscs2001_uni2indx_page287[(wc>>4)-0x2870];
        else if (wc >= 0x28900 && wc < 0x28af0)
          summary = &hkscs2001_uni2indx_page289[(wc>>4)-0x2890];
        else if (wc >= 0x28d00 && wc < 0x28dc0)
          summary = &hkscs2001_uni2indx_page28d[(wc>>4)-0x28d0];
        else if (wc >= 0x29900 && wc < 0x29950)
          summary = &hkscs2001_uni2indx_page299[(wc>>4)-0x2990];
        else if (wc >= 0x29c00 && wc < 0x29c80)
          summary = &hkscs2001_uni2indx_page29c[(wc>>4)-0x29c0];
        else if (wc >= 0x2a100 && wc < 0x2a2c0)
          summary = &hkscs2001_uni2indx_page2a1[(wc>>4)-0x2a10];
      }
    }
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
        c = hkscs2001_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
        return 2;
      }
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}