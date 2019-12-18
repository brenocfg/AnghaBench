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
 scalar_t__ STREQ (char const*,char*) ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char* get_version_string () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
gopt_print_version(const char *val)
{
  if (STREQ(val, "yes")) {
    char *vers = get_version_string();
    fputs(vers, stderr);
    XFREE(vers);
    return 0;
  } else if (STREQ(val, "no")) {
    return 0;
  }

  fprintf(stderr, "conf: unknown value to print_version \"%s\"\n", val);
  return 1;			/* unknown value */
}