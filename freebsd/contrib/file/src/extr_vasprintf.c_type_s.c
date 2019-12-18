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
typedef  int /*<<< orphan*/  xprintf_struct ;

/* Variables and functions */
 int print_it (int /*<<< orphan*/ *,size_t,char const*,char const*) ; 

__attribute__((used)) static int type_s(xprintf_struct *s, int width, int prec,
                  const char *format_string, const char *arg_string)
{
  size_t string_len;

  if (arg_string == NULL)
    return print_it(s, (size_t)6, "(null)", 0);

  /* hand-made strlen() whitch stops when 'prec' is reached. */
  /* if 'prec' is -1 then it is never reached. */
  string_len = 0;
  while (arg_string[string_len] != 0 && (size_t)prec != string_len)
    string_len++;

  if (width != -1 && string_len < (size_t)width)
    string_len = (size_t)width;

  return print_it(s, string_len, format_string, arg_string);
}