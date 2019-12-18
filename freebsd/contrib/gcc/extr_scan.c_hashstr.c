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

/* Variables and functions */

unsigned int
hashstr (const char *str, unsigned int len)
{
  unsigned int n = len;
  unsigned int r = 0;
  const unsigned char *s = (const unsigned char *) str;

  do
    r = r * 67 + (*s++ - 113);
  while (--n);
  return r + len;
}