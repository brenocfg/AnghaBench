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
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 scalar_t__ ISDIGIT (unsigned char) ; 
 char* char_str ; 
 int /*<<< orphan*/  string_append (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
snarf_numeric_literal (const char **args, string *arg)
{
  if (**args == '-')
    {
      char_str[0] = '-';
      string_append (arg, char_str);
      (*args)++;
    }
  else if (**args == '+')
    (*args)++;

  if (!ISDIGIT ((unsigned char)**args))
    return 0;

  while (ISDIGIT ((unsigned char)**args))
    {
      char_str[0] = **args;
      string_append (arg, char_str);
      (*args)++;
    }

  return 1;
}