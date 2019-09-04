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
 int RET_TOOSMALL ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static int
ucs4swapped_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  /* This function assumes that 'unsigned int' has exactly 32 bits. */
  if (sizeof(unsigned int) != 4) abort();

  if (n >= 4) {
    unsigned int x = wc;
    x = (x >> 24) | ((x >> 8) & 0xff00) | ((x & 0xff00) << 8) | (x << 24);
    *(unsigned int *)r = x;
    return 4;
  } else
    return RET_TOOSMALL;
}