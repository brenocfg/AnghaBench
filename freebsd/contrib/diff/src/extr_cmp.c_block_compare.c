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
typedef  scalar_t__ word ;

/* Variables and functions */

__attribute__((used)) static size_t
block_compare (word const *p0, word const *p1)
{
  word const *l0, *l1;
  char const *c0, *c1;

  /* Find the rough position of the first difference by reading words,
     not bytes.  */

  for (l0 = p0, l1 = p1;  *l0 == *l1;  l0++, l1++)
    continue;

  /* Find the exact differing position (endianness independent).  */

  for (c0 = (char const *) l0, c1 = (char const *) l1;
       *c0 == *c1;
       c0++, c1++)
    continue;

  return c0 - (char const *) p0;
}