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
typedef  scalar_t__ ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 unsigned int* gb18030uni_charset2uni_ranges ; 
 unsigned int* gb18030uni_ranges ; 

__attribute__((used)) static int
gb18030uni_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  unsigned char c1 = s[0];
  if (c1 >= 0x81 && c1 <= 0x84) {
    if (n >= 2) {
      unsigned char c2 = s[1];
      if (c2 >= 0x30 && c2 <= 0x39) {
        if (n >= 3) {
          unsigned char c3 = s[2];
          if (c3 >= 0x81 && c3 <= 0xfe) {
            if (n >= 4) {
              unsigned char c4 = s[3];
              if (c4 >= 0x30 && c4 <= 0x39) {
                unsigned int i = (((c1 - 0x81) * 10 + (c2 - 0x30)) * 126 + (c3 - 0x81)) * 10 + (c4 - 0x30);
                if (i >= 0 && i <= 39419) {
                  unsigned int k1 = 0;
                  unsigned int k2 = 205;
                  while (k1 < k2) {
                    unsigned int k = (k1 + k2) / 2;
                    if (i <= gb18030uni_charset2uni_ranges[2*k+1])
                      k2 = k;
                    else if (i >= gb18030uni_charset2uni_ranges[2*k+2])
                      k1 = k + 1;
                    else
                      return RET_ILSEQ;
                  }
                  {
                    unsigned int diff = gb18030uni_ranges[k1];
                    *pwc = (ucs4_t) (i + diff);
                    return 4;
                  }
                }
              }
              return RET_ILSEQ;
            }
            return RET_TOOFEW(0);
          }
          return RET_ILSEQ;
        }
        return RET_TOOFEW(0);
      }
      return RET_ILSEQ;
    }
    return RET_TOOFEW(0);
  }
  return RET_ILSEQ;
}