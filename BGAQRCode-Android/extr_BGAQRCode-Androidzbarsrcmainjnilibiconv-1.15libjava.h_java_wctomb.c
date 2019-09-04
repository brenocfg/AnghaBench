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
 int RET_TOOSMALL ; 

__attribute__((used)) static int
java_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (wc < 0x80) {
    *r = wc;
    return 1;
  } else if (wc < 0x10000) {
    if (n >= 6) {
      unsigned int i;
      r[0] = '\\';
      r[1] = 'u';
      i = (wc >> 12) & 0x0f; r[2] = (i < 10 ? '0'+i : 'a'-10+i);
      i = (wc >> 8) & 0x0f;  r[3] = (i < 10 ? '0'+i : 'a'-10+i);
      i = (wc >> 4) & 0x0f;  r[4] = (i < 10 ? '0'+i : 'a'-10+i);
      i = wc & 0x0f;         r[5] = (i < 10 ? '0'+i : 'a'-10+i);
      return 6;
    } else
      return RET_TOOSMALL;
  } else if (wc < 0x110000) {
    if (n >= 12) {
      ucs4_t wc1 = 0xd800 + ((wc - 0x10000) >> 10);
      ucs4_t wc2 = 0xdc00 + ((wc - 0x10000) & 0x3ff);
      unsigned int i;
      r[0] = '\\';
      r[1] = 'u';
      i = (wc1 >> 12) & 0x0f; r[2] = (i < 10 ? '0'+i : 'a'-10+i);
      i = (wc1 >> 8) & 0x0f;  r[3] = (i < 10 ? '0'+i : 'a'-10+i);
      i = (wc1 >> 4) & 0x0f;  r[4] = (i < 10 ? '0'+i : 'a'-10+i);
      i = wc1 & 0x0f;         r[5] = (i < 10 ? '0'+i : 'a'-10+i);
      r[6] = '\\';
      r[7] = 'u';
      i = (wc2 >> 12) & 0x0f; r[8] = (i < 10 ? '0'+i : 'a'-10+i);
      i = (wc2 >> 8) & 0x0f;  r[9] = (i < 10 ? '0'+i : 'a'-10+i);
      i = (wc2 >> 4) & 0x0f; r[10] = (i < 10 ? '0'+i : 'a'-10+i);
      i = wc2 & 0x0f;        r[11] = (i < 10 ? '0'+i : 'a'-10+i);
      return 12;
    } else
      return RET_TOOSMALL;
  }
  return RET_ILUNI;
}