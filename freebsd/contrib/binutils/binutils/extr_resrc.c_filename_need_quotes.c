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
filename_need_quotes (const char *filename)
{
  if (filename == NULL || (filename[0] == '-' && filename[1] == 0))
    return 0;

  while (*filename != 0)
    {
      switch (*filename)
        {
        case '&':
        case ' ':
        case '<':
        case '>':
        case '|':
        case '%':
          return 1;
        }
      ++filename;
    }
  return 0;
}