#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* error; } ;

/* Variables and functions */
 void* BAD_SKIP_COMMA ; 
 scalar_t__ FAIL ; 
 int SUCCESS ; 
 TYPE_1__ inst ; 

__attribute__((used)) static int
skip_past_comma (char **str)
{
  char *p = *str;
  char c;
  int comma = 0;

  while ((c = *p) == ' ' || c == ',')
    {
      p++;
      if (c == ',' && comma++)
        {
          inst.error = BAD_SKIP_COMMA;
          return (int) FAIL;
        }
    }

  if ((c == '\0') || (comma == 0))
    {
      inst.error = BAD_SKIP_COMMA;
      return (int) FAIL;
    }

  *str = p;
  return comma ? SUCCESS : (int) FAIL;
}