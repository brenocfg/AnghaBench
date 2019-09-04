#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_1__ ;

/* Type definitions */
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;
struct TYPE_52__ {unsigned short used; unsigned short indx; } ;
typedef  TYPE_1__ Summary16 ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 unsigned short* hkscs2004_2charset ; 
 TYPE_1__* hkscs2004_uni2indx_page201 ; 
 TYPE_1__* hkscs2004_uni2indx_page20a ; 
 TYPE_1__* hkscs2004_uni2indx_page21a ; 
 TYPE_1__* hkscs2004_uni2indx_page21d ; 
 TYPE_1__* hkscs2004_uni2indx_page221 ; 
 TYPE_1__* hkscs2004_uni2indx_page227 ; 
 TYPE_1__* hkscs2004_uni2indx_page232 ; 
 TYPE_1__* hkscs2004_uni2indx_page235 ; 
 TYPE_1__* hkscs2004_uni2indx_page23b ; 
 TYPE_1__* hkscs2004_uni2indx_page23e ; 
 TYPE_1__* hkscs2004_uni2indx_page242 ; 
 TYPE_1__* hkscs2004_uni2indx_page24b ; 
 TYPE_1__* hkscs2004_uni2indx_page254 ; 
 TYPE_1__* hkscs2004_uni2indx_page25a ; 
 TYPE_1__* hkscs2004_uni2indx_page26b ; 
 TYPE_1__* hkscs2004_uni2indx_page26e ; 
 TYPE_1__* hkscs2004_uni2indx_page270 ; 
 TYPE_1__* hkscs2004_uni2indx_page272 ; 
 TYPE_1__* hkscs2004_uni2indx_page27b ; 
 TYPE_1__* hkscs2004_uni2indx_page286 ; 
 TYPE_1__* hkscs2004_uni2indx_page289 ; 
 TYPE_1__* hkscs2004_uni2indx_page28b ; 
 TYPE_1__* hkscs2004_uni2indx_page290 ; 
 TYPE_1__* hkscs2004_uni2indx_page298 ; 
 TYPE_1__* hkscs2004_uni2indx_page29e ; 
 TYPE_1__* hkscs2004_uni2indx_page2a1 ; 
 TYPE_1__* hkscs2004_uni2indx_page2a3 ; 
 TYPE_1__* hkscs2004_uni2indx_page34 ; 
 TYPE_1__* hkscs2004_uni2indx_page36 ; 
 TYPE_1__* hkscs2004_uni2indx_page3b ; 
 TYPE_1__* hkscs2004_uni2indx_page3d ; 
 TYPE_1__* hkscs2004_uni2indx_page3f ; 
 TYPE_1__* hkscs2004_uni2indx_page43 ; 
 TYPE_1__* hkscs2004_uni2indx_page4a ; 
 TYPE_1__* hkscs2004_uni2indx_page4c ; 
 TYPE_1__* hkscs2004_uni2indx_page4f ; 
 TYPE_1__* hkscs2004_uni2indx_page56 ; 
 TYPE_1__* hkscs2004_uni2indx_page59 ; 
 TYPE_1__* hkscs2004_uni2indx_page5f ; 
 TYPE_1__* hkscs2004_uni2indx_page66 ; 
 TYPE_1__* hkscs2004_uni2indx_page6e ; 
 TYPE_1__* hkscs2004_uni2indx_page71 ; 
 TYPE_1__* hkscs2004_uni2indx_page74 ; 
 TYPE_1__* hkscs2004_uni2indx_page79 ; 
 TYPE_1__* hkscs2004_uni2indx_page7d ; 
 TYPE_1__* hkscs2004_uni2indx_page81 ; 
 TYPE_1__* hkscs2004_uni2indx_page85 ; 
 TYPE_1__* hkscs2004_uni2indx_page8a ; 
 TYPE_1__* hkscs2004_uni2indx_page97 ; 
 TYPE_1__* hkscs2004_uni2indx_page9f ; 

__attribute__((used)) static int
hkscs2004_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 2) {
    const Summary16 *summary = NULL;
    if (wc < 0x21a00) {
      if (wc < 0x6e00) {
        if (wc >= 0x3400 && wc < 0x3450)
          summary = &hkscs2004_uni2indx_page34[(wc>>4)-0x340];
        else if (wc >= 0x3600 && wc < 0x3980)
          summary = &hkscs2004_uni2indx_page36[(wc>>4)-0x360];
        else if (wc >= 0x3b00 && wc < 0x3ba0)
          summary = &hkscs2004_uni2indx_page3b[(wc>>4)-0x3b0];
        else if (wc >= 0x3d00 && wc < 0x3e00)
          summary = &hkscs2004_uni2indx_page3d[(wc>>4)-0x3d0];
        else if (wc >= 0x3f00 && wc < 0x41f0)
          summary = &hkscs2004_uni2indx_page3f[(wc>>4)-0x3f0];
        else if (wc >= 0x4300 && wc < 0x4750)
          summary = &hkscs2004_uni2indx_page43[(wc>>4)-0x430];
        else if (wc >= 0x4a00 && wc < 0x4ab0)
          summary = &hkscs2004_uni2indx_page4a[(wc>>4)-0x4a0];
        else if (wc >= 0x4c00 && wc < 0x4d90)
          summary = &hkscs2004_uni2indx_page4c[(wc>>4)-0x4c0];
        else if (wc >= 0x4f00 && wc < 0x4fc0)
          summary = &hkscs2004_uni2indx_page4f[(wc>>4)-0x4f0];
        else if (wc >= 0x5600 && wc < 0x5700)
          summary = &hkscs2004_uni2indx_page56[(wc>>4)-0x560];
        else if (wc >= 0x5900 && wc < 0x5d80)
          summary = &hkscs2004_uni2indx_page59[(wc>>4)-0x590];
        else if (wc >= 0x5f00 && wc < 0x5f40)
          summary = &hkscs2004_uni2indx_page5f[(wc>>4)-0x5f0];
        else if (wc >= 0x6600 && wc < 0x6770)
          summary = &hkscs2004_uni2indx_page66[(wc>>4)-0x660];
      } else {
        if (wc >= 0x6e00 && wc < 0x6e60)
          summary = &hkscs2004_uni2indx_page6e[(wc>>4)-0x6e0];
        else if (wc >= 0x7100 && wc < 0x7230)
          summary = &hkscs2004_uni2indx_page71[(wc>>4)-0x710];
        else if (wc >= 0x7400 && wc < 0x74a0)
          summary = &hkscs2004_uni2indx_page74[(wc>>4)-0x740];
        else if (wc >= 0x7900 && wc < 0x79d0)
          summary = &hkscs2004_uni2indx_page79[(wc>>4)-0x790];
        else if (wc >= 0x7d00 && wc < 0x7da0)
          summary = &hkscs2004_uni2indx_page7d[(wc>>4)-0x7d0];
        else if (wc >= 0x8100 && wc < 0x8170)
          summary = &hkscs2004_uni2indx_page81[(wc>>4)-0x810];
        else if (wc >= 0x8500 && wc < 0x85a0)
          summary = &hkscs2004_uni2indx_page85[(wc>>4)-0x850];
        else if (wc >= 0x8a00 && wc < 0x8b00)
          summary = &hkscs2004_uni2indx_page8a[(wc>>4)-0x8a0];
        else if (wc >= 0x9700 && wc < 0x9860)
          summary = &hkscs2004_uni2indx_page97[(wc>>4)-0x970];
        else if (wc >= 0x9f00 && wc < 0x9fc0)
          summary = &hkscs2004_uni2indx_page9f[(wc>>4)-0x9f0];
        else if (wc >= 0x20100 && wc < 0x20240)
          summary = &hkscs2004_uni2indx_page201[(wc>>4)-0x2010];
        else if (wc >= 0x20a00 && wc < 0x20ba0)
          summary = &hkscs2004_uni2indx_page20a[(wc>>4)-0x20a0];
      }
    } else {
      if (wc < 0x26b00) {
        if (wc >= 0x21a00 && wc < 0x21a70)
          summary = &hkscs2004_uni2indx_page21a[(wc>>4)-0x21a0];
        else if (wc >= 0x21d00 && wc < 0x21e30)
          summary = &hkscs2004_uni2indx_page21d[(wc>>4)-0x21d0];
        else if (wc >= 0x22100 && wc < 0x221d0)
          summary = &hkscs2004_uni2indx_page221[(wc>>4)-0x2210];
        else if (wc >= 0x22700 && wc < 0x227a0)
          summary = &hkscs2004_uni2indx_page227[(wc>>4)-0x2270];
        else if (wc >= 0x23200 && wc < 0x23260)
          summary = &hkscs2004_uni2indx_page232[(wc>>4)-0x2320];
        else if (wc >= 0x23500 && wc < 0x23620)
          summary = &hkscs2004_uni2indx_page235[(wc>>4)-0x2350];
        else if (wc >= 0x23b00 && wc < 0x23b20)
          summary = &hkscs2004_uni2indx_page23b[(wc>>4)-0x23b0];
        else if (wc >= 0x23e00 && wc < 0x240f0)
          summary = &hkscs2004_uni2indx_page23e[(wc>>4)-0x23e0];
        else if (wc >= 0x24200 && wc < 0x242c0)
          summary = &hkscs2004_uni2indx_page242[(wc>>4)-0x2420];
        else if (wc >= 0x24b00 && wc < 0x24b10)
          summary = &hkscs2004_uni2indx_page24b[(wc>>4)-0x24b0];
        else if (wc >= 0x25400 && wc < 0x254a0)
          summary = &hkscs2004_uni2indx_page254[(wc>>4)-0x2540];
        else if (wc >= 0x25a00 && wc < 0x25a60)
          summary = &hkscs2004_uni2indx_page25a[(wc>>4)-0x25a0];
      } else {
        if (wc >= 0x26b00 && wc < 0x26c50)
          summary = &hkscs2004_uni2indx_page26b[(wc>>4)-0x26b0];
        else if (wc >= 0x26e00 && wc < 0x26e90)
          summary = &hkscs2004_uni2indx_page26e[(wc>>4)-0x26e0];
        else if (wc >= 0x27000 && wc < 0x270e0)
          summary = &hkscs2004_uni2indx_page270[(wc>>4)-0x2700];
        else if (wc >= 0x27200 && wc < 0x27400)
          summary = &hkscs2004_uni2indx_page272[(wc>>4)-0x2720];
        else if (wc >= 0x27b00 && wc < 0x27cd0)
          summary = &hkscs2004_uni2indx_page27b[(wc>>4)-0x27b0];
        else if (wc >= 0x28600 && wc < 0x286c0)
          summary = &hkscs2004_uni2indx_page286[(wc>>4)-0x2860];
        else if (wc >= 0x28900 && wc < 0x28970)
          summary = &hkscs2004_uni2indx_page289[(wc>>4)-0x2890];
        else if (wc >= 0x28b00 && wc < 0x28bc0)
          summary = &hkscs2004_uni2indx_page28b[(wc>>4)-0x28b0];
        else if (wc >= 0x29000 && wc < 0x29080)
          summary = &hkscs2004_uni2indx_page290[(wc>>4)-0x2900];
        else if (wc >= 0x29800 && wc < 0x29950)
          summary = &hkscs2004_uni2indx_page298[(wc>>4)-0x2980];
        else if (wc >= 0x29e00 && wc < 0x29ec0)
          summary = &hkscs2004_uni2indx_page29e[(wc>>4)-0x29e0];
        else if (wc >= 0x2a100 && wc < 0x2a1c0)
          summary = &hkscs2004_uni2indx_page2a1[(wc>>4)-0x2a10];
        else if (wc >= 0x2a300 && wc < 0x2a360)
          summary = &hkscs2004_uni2indx_page2a3[(wc>>4)-0x2a30];
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
        c = hkscs2004_2charset[summary->indx + used];
        r[0] = (c >> 8); r[1] = (c & 0xff);
        return 2;
      }
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}