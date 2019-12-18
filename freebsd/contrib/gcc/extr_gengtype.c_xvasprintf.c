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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xexit (int) ; 

int
xvasprintf (char **result, const char *format, va_list args)
{
  int ret = vasprintf (result, format, args);
  if (*result == NULL || ret < 0)
    {
      fputs ("gengtype: out of memory", stderr);
      xexit (1);
    }
  return ret;
}