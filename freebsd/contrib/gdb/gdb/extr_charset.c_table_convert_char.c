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

__attribute__((used)) static int
table_convert_char (void *baton, int from, int *to)
{
  int *table = (int *) baton;

  if (0 <= from && from <= 255
      && table[from] != -1)
    {
      *to = table[from];
      return 1;
    }
  else
    return 0;
}