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
 unsigned char* cp1129_page00 ; 
 unsigned char* cp1129_page03 ; 
 unsigned char* cp1163_page20 ; 

__attribute__((used)) static int
cp1163_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  unsigned char c = 0;
  if (wc < 0x00a0 || (wc < 0x00a8 && wc != 0x00a4) || wc == 0x00d0) {
    *r = wc;
    return 1;
  }
  else if (wc >= 0x00a8 && wc < 0x01b8)
    c = cp1129_page00[wc-0x00a8];
  else if (wc >= 0x0300 && wc < 0x0328)
    c = cp1129_page03[wc-0x0300];
  else if (wc == 0x203e)
    c = 0xaf;
  else if (wc >= 0x20a8 && wc < 0x20b0)
    c = cp1163_page20[wc-0x20a8];
  if (c != 0) {
    *r = c;
    return 1;
  }
  return RET_ILUNI;
}