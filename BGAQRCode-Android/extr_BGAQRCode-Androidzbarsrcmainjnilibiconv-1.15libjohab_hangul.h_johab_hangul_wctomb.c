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
 int* jamo_final_index_inverse ; 
 int* jamo_initial_index_inverse ; 
 int* jamo_medial_index_inverse ; 
 unsigned short* johab_hangul_page31 ; 

__attribute__((used)) static int
johab_hangul_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 2) {
    if (wc >= 0x3131 && wc < 0x3164) {
      unsigned short c = johab_hangul_page31[wc-0x3131];
      r[0] = (c >> 8); r[1] = (c & 0xff);
      return 2;
    } else if (wc >= 0xac00 && wc < 0xd7a4) {
      unsigned int index1;
      unsigned int index2;
      unsigned int index3;
      unsigned short c;
      unsigned int tmp = wc - 0xac00;
      index3 = tmp % 28; tmp = tmp / 28;
      index2 = tmp % 21; tmp = tmp / 21;
      index1 = tmp;
      c = (((((1 << 5)
              | jamo_initial_index_inverse[index1]) << 5)
            | jamo_medial_index_inverse[index2]) << 5)
          | jamo_final_index_inverse[index3];
      r[0] = (c >> 8); r[1] = (c & 0xff);
      return 2;
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}