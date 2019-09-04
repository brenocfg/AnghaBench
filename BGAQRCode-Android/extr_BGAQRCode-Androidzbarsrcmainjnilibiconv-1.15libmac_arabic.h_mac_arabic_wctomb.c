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
 unsigned char* mac_arabic_page00 ; 
 unsigned char* mac_arabic_page06 ; 

__attribute__((used)) static int
mac_arabic_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0080) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x00a0 && wc < 0x0100)
    c = mac_arabic_page00[wc-0x00a0];
  else if (wc >= 0x0608 && wc < 0x06d8)
    c = mac_arabic_page06[wc-0x0608];
  else if (wc == 0x2026)
    c = 0x93;
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}