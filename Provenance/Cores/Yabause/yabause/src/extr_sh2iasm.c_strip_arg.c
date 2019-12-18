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

int strip_arg(const char *str,char *arg)

// Strip out next arg in the string

{
    int pos;

    pos = 0;
    if(str[0] == '@')
    {
      if(str[1] == '(')
      {
        if(str[2] != 0)
        {
        do
        {
           arg[pos] = str[pos];
           pos++;
        }
        while((str[pos-1] != ')') && (str[pos] != 0));

        }
      }
      else
        while((str[pos] != ',') && (str[pos] != 0))
        {
           arg[pos] = str[pos];
           pos++;
        }
    }
    else
      while((str[pos] != ',') && (str[pos] != 0))
      {
          arg[pos] = str[pos];
          pos++;
      }

    arg[pos] = 0;

    return pos;
}