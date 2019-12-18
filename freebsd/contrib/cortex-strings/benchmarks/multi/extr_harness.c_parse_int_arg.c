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
 scalar_t__ errno ; 
 long strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char const*) ; 

__attribute__((used)) static int parse_int_arg(const char *arg, const char *exe_name)
{
  long int ret;

  errno = 0;
  ret = strtol(arg, NULL, 0);

  if (errno)
    {
      usage(exe_name);
    }

  return (int)ret;
}