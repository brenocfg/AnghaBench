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
 scalar_t__ alloca (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  run_directive (int /*<<< orphan*/ *,int,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
handle_assertion (cpp_reader *pfile, const char *str, int type)
{
  size_t count = strlen (str);
  const char *p = strchr (str, '=');

  /* Copy the entire option so we can modify it.  Change the first
     "=" in the string to a '(', and tack a ')' on the end.  */
  char *buf = (char *) alloca (count + 2);

  memcpy (buf, str, count);
  if (p)
    {
      buf[p - str] = '(';
      buf[count++] = ')';
    }
  buf[count] = '\n';
  str = buf;

  run_directive (pfile, type, str, count);
}