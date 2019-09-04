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
typedef  unsigned int ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILUNI ; 
 int RET_TOOSMALL ; 
 unsigned int* gb18030uni_ranges ; 
 unsigned int* gb18030uni_uni2charset_ranges ; 

__attribute__((used)) static int
gb18030uni_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 4) {
    unsigned int i = wc;
    if (i >= 0x0080 && i <= 0xffff) {
      if (i == 0xe7c7) {
        i = 7457;
      } else {
        unsigned int k1 = 0;
        unsigned int k2 = 205;
        while (k1 < k2) {
          unsigned int k = (k1 + k2) / 2;
          if (i <= gb18030uni_uni2charset_ranges[2*k+1])
            k2 = k;
          else if (i >= gb18030uni_uni2charset_ranges[2*k+2])
            k1 = k + 1;
          else
            return RET_ILUNI;
        }
        {
          unsigned int diff = gb18030uni_ranges[k1];
          i -= diff;
        }
      }
      r[3] = (i % 10) + 0x30; i = i / 10;
      r[2] = (i % 126) + 0x81; i = i / 126;
      r[1] = (i % 10) + 0x30; i = i / 10;
      r[0] = i + 0x81;
      return 4;
    }
    return RET_ILUNI;
  }
  return RET_TOOSMALL;
}