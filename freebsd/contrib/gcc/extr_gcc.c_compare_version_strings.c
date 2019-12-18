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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int REG_EXTENDED ; 
 int REG_NOMATCH ; 
 int REG_NOSUB ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char*,int) ; 
 int regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strverscmp (char const*,char const*) ; 

__attribute__((used)) static int
compare_version_strings (const char *v1, const char *v2)
{
  int rresult;
  regex_t r;

  if (regcomp (&r, "^([1-9][0-9]*|0)(\\.([1-9][0-9]*|0))*$",
	       REG_EXTENDED | REG_NOSUB) != 0)
    abort ();
  rresult = regexec (&r, v1, 0, NULL, 0);
  if (rresult == REG_NOMATCH)
    fatal ("invalid version number `%s'", v1);
  else if (rresult != 0)
    abort ();
  rresult = regexec (&r, v2, 0, NULL, 0);
  if (rresult == REG_NOMATCH)
    fatal ("invalid version number `%s'", v2);
  else if (rresult != 0)
    abort ();

  return strverscmp (v1, v2);
}