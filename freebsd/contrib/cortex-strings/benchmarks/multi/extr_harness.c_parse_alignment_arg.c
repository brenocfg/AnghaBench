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
 int /*<<< orphan*/  printf (char*) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char const*) ; 

__attribute__((used)) static void parse_alignment_arg(const char *arg, const char *exe_name,
				int *src_alignment, int *dst_alignment)
{
  long int ret;
  char *endptr;

  errno = 0;
  ret = strtol(arg, &endptr, 0);

  if (errno)
    {
      usage(exe_name);
    }

  *src_alignment = (int)ret;

  if (ret > 256 || ret < 1)
    {
      printf("Alignment should be in the range [1, 256].\n");
      usage(exe_name);
    }

  if (ret == 256)
    ret = 0;

  if (endptr && *endptr == ':')
    {
      errno = 0;
      ret = strtol(endptr + 1, NULL, 0);

      if (errno)
	{
	  usage(exe_name);
	}

      if (ret > 256 || ret < 1)
	{
	  printf("Alignment should be in the range [1, 256].\n");
	  usage(exe_name);
	}

      if (ret == 256)
	ret = 0;
    }

  *dst_alignment = (int)ret;
}