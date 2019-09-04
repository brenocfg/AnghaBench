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
 unsigned char* cp852_page00 ; 
 unsigned char* cp852_page02 ; 
 unsigned char* cp852_page25 ; 

__attribute__((used)) static int
cp852_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x0080) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x00a0 && wc < 0x0180)
    c = cp852_page00[wc-0x00a0];
  else if (wc >= 0x02c0 && wc < 0x02e0)
    c = cp852_page02[wc-0x02c0];
  else if (wc >= 0x2500 && wc < 0x25a8)
    c = cp852_page25[wc-0x2500];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}