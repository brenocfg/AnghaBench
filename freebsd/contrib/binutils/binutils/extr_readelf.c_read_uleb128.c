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

__attribute__((used)) static unsigned int
read_uleb128 (unsigned char *p, unsigned int *plen)
{
  unsigned char c;
  unsigned int val;
  int shift;
  int len;

  val = 0;
  shift = 0;
  len = 0;
  do
    {
      c = *(p++);
      len++;
      val |= ((unsigned int)c & 0x7f) << shift;
      shift += 7;
    }
  while (c & 0x80);

  *plen = len;
  return val;
}