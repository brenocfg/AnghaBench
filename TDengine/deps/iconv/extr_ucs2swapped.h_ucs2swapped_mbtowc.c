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
typedef  unsigned short ucs4_t ;
typedef  int /*<<< orphan*/  conv_t ;

/* Variables and functions */
 int RET_ILSEQ ; 
 int RET_TOOFEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static int
ucs2swapped_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, int n)
{
  /* This function assumes that 'unsigned short' has exactly 16 bits. */
  if (sizeof(unsigned short) != 2) abort();

  if (n >= 2) {
    unsigned short x = *(const unsigned short *)s;
    x = (x >> 8) | (x << 8);
    if (x >= 0xd800 && x < 0xe000) {
      return RET_ILSEQ;
    } else {
      *pwc = x;
      return 2;
    }
  }
  return RET_TOOFEW(0);
}