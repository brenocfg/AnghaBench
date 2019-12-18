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
 scalar_t__ ISDIGIT (char const) ; 
 int /*<<< orphan*/  OPT_Wformat ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
avoid_dollar_number (const char *format)
{
  if (!ISDIGIT (*format))
    return false;
  while (ISDIGIT (*format))
    format++;
  if (*format == '$')
    {
      warning (OPT_Wformat, "$ operand number used after format without operand number");
      return true;
    }
  return false;
}