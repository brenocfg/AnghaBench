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
 scalar_t__* cp850_2uni ; 

__attribute__((used)) static int
cp858_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n)
{
  unsigned char c = *s;
  if (c < 0x80)
    *pwc = (ucs4_t) c;
  else if (c == 0xd5)
    *pwc = 0x20ac;
  else
    *pwc = (ucs4_t) cp850_2uni[c-0x80];
  return 1;
}