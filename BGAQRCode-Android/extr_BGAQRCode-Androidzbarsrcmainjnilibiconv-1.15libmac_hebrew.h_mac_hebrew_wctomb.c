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
 unsigned char* mac_hebrew_page00 ; 
 unsigned char* mac_hebrew_page05 ; 
 unsigned char* mac_hebrew_page20 ; 
 unsigned char* mac_hebrew_pagefb ; 

__attribute__((used)) static int
mac_hebrew_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0080) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x00a0 && wc < 0x0100)
    c = mac_hebrew_page00[wc-0x00a0];
  else if (wc >= 0x05b0 && wc < 0x05f0)
    c = mac_hebrew_page05[wc-0x05b0];
  else if (wc >= 0x2010 && wc < 0x2028)
    c = mac_hebrew_page20[wc-0x2010];
  else if (wc == 0x20aa)
    c = 0xa6;
  else if (wc >= 0xfb18 && wc < 0xfb50)
    c = mac_hebrew_pagefb[wc-0xfb18];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}