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

__attribute__((used)) static int
iso646_jp_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, size_t n)
{
  if (wc < 0x0080 && !(wc == 0x005c || wc == 0x007e)) {
    *r = wc;
    return 1;
  }
  if (wc == 0x00a5) {
    *r = 0x5c;
    return 1;
  }
  if (wc == 0x203e) {
    *r = 0x7e;
    return 1;
  }
  return RET_ILUNI;
}