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
 scalar_t__* cp922_2uni_1 ; 
 scalar_t__* cp922_2uni_2 ; 
 scalar_t__* cp922_2uni_3 ; 

__attribute__((used)) static int
cp922_mbtowc (conv_t conv, ucs4_t *pwc, const unsigned char *s, size_t n)
{
  unsigned char c = *s;
  if (c < 0xa0)
    *pwc = (ucs4_t) c;
  else if (c < 0xb0)
    *pwc = (ucs4_t) cp922_2uni_1[c-0xa0];
  else if (c < 0xd0)
    *pwc = (ucs4_t) c;
  else if (c < 0xe0)
    *pwc = (ucs4_t) cp922_2uni_2[c-0xd0];
  else if (c < 0xf0)
    *pwc = (ucs4_t) c;
  else
    *pwc = (ucs4_t) cp922_2uni_3[c-0xf0];
  return 1;
}