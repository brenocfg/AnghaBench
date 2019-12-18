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
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  T_DEFINE ; 
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  run_directive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

void
cpp_define (cpp_reader *pfile, const char *str)
{
  char *buf, *p;
  size_t count;

  /* Copy the entire option so we can modify it.
     Change the first "=" in the string to a space.  If there is none,
     tack " 1" on the end.  */

  count = strlen (str);
  buf = (char *) alloca (count + 3);
  memcpy (buf, str, count);

  p = strchr (str, '=');
  if (p)
    buf[p - str] = ' ';
  else
    {
      buf[count++] = ' ';
      buf[count++] = '1';
    }
  buf[count] = '\n';

  run_directive (pfile, T_DEFINE, buf, count);
}