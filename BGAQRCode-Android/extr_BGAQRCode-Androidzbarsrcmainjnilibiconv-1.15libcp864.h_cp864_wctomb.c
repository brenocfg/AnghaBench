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
typedef  int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILUNI ; 
 unsigned char* cp864_page00 ; 
 unsigned char* cp864_page00_1 ; 
 unsigned char* cp864_page06 ; 
 unsigned char* cp864_page22 ; 
 unsigned char* cp864_page25 ; 
 unsigned char* cp864_pagefe ; 

__attribute__((used)) static int
cp864_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0020) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x0020 && wc < 0x0028)
    c = cp864_page00[wc-0x0020];
  else if (wc >= 0x0028 && wc < 0x0080)
    c = wc;
  else if (wc >= 0x00a0 && wc < 0x00f8)
    c = cp864_page00_1[wc-0x00a0];
  else if (wc == 0x03b2)
    c = 0x90;
  else if (wc == 0x03c6)
    c = 0x92;
  else if (wc >= 0x0608 && wc < 0x0670)
    c = cp864_page06[wc-0x0608];
  else if (wc >= 0x2218 && wc < 0x2250)
    c = cp864_page22[wc-0x2218];
  else if (wc >= 0x2500 && wc < 0x2540)
    c = cp864_page25[wc-0x2500];
  else if (wc == 0x2592)
    c = 0x84;
  else if (wc == 0x25a0)
    c = 0xfe;
  else if (wc >= 0xfe78 && wc < 0xff00)
    c = cp864_pagefe[wc-0xfe78];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}