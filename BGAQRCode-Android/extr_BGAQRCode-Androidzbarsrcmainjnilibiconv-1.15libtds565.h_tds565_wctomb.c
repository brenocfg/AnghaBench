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
 unsigned char* tds565_page00 ; 
 unsigned char* tds565_page00_1 ; 
 unsigned char* tds565_page01 ; 

__attribute__((used)) static int
tds565_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0040) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x0040 && wc < 0x0080)
    c = tds565_page00[wc-0x0040];
  else if (wc >= 0x00c0 && wc < 0x0100)
    c = tds565_page00_1[wc-0x00c0];
  else if (wc >= 0x0140 && wc < 0x0180)
    c = tds565_page01[wc-0x0140];
  else if (wc == 0x2116)
    c = 0x60;
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}