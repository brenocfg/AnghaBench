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
 unsigned char* rk1048_page00 ; 
 unsigned char* rk1048_page04 ; 
 unsigned char* rk1048_page20 ; 
 unsigned char* rk1048_page21 ; 

__attribute__((used)) static int
rk1048_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0080) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x00a0 && wc < 0x00c0)
    c = rk1048_page00[wc-0x00a0];
  else if (wc >= 0x0400 && wc < 0x04f0)
    c = rk1048_page04[wc-0x0400];
  else if (wc >= 0x2010 && wc < 0x2040)
    c = rk1048_page20[wc-0x2010];
  else if (wc == 0x20ac)
    c = 0x88;
  else if (wc >= 0x2110 && wc < 0x2128)
    c = rk1048_page21[wc-0x2110];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}