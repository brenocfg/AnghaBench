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
 int RET_TOOSMALL ; 

__attribute__((used)) static int
ucs4le_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (n >= 4) {
    r[0] = (unsigned char) wc;
    r[1] = (unsigned char) (wc >> 8);
    r[2] = (unsigned char) (wc >> 16);
    r[3] = (unsigned char) (wc >> 24);
    return 4;
  } else
    return RET_TOOSMALL;
}