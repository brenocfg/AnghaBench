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

__attribute__((used)) static void
writeBITS (int val, unsigned char *ptr, int *idx, int size)
{
  int byte = *idx / 8;
  int bit = *idx % 8;
  int old;

  *idx += size;

  old = ptr[byte];
  /* Turn off all about to change bits.  */
  old &= ~((~0 >> (8 - bit - size)) & ((1 << size) - 1));
  /* Turn on the bits we want.  */
  old |= (val & ((1 << size) - 1)) << (8 - bit - size);
  ptr[byte] = old;
}