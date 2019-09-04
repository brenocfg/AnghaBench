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
 unsigned char* riscos1_page01 ; 
 unsigned char* riscos1_page20 ; 
 unsigned char* riscos1_page21 ; 
 unsigned char* riscos1_page22 ; 

__attribute__((used)) static int
riscos1_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0080 || wc == 0x0083 || wc == 0x0087 || (wc >= 0x00a0 && wc < 0x0100)) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x0150 && wc < 0x0178)
    c = riscos1_page01[wc-0x0150];
  else if (wc >= 0x2010 && wc < 0x2040)
    c = riscos1_page20[wc-0x2010];
  else if (wc == 0x2122)
    c = 0x8d;
  else if (wc >= 0x21e0 && wc < 0x21f0)
    c = riscos1_page21[wc-0x21e0];
  else if (wc >= 0x2210 && wc < 0x2220)
    c = riscos1_page22[wc-0x2210];
  else if (wc == 0x2573)
    c = 0x84;
  else if (wc >= 0xfb01 && wc < 0xfb03)
    c = wc-0xfa63;
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}