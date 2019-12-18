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
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int integral_argument (char*) ; 
 int /*<<< orphan*/  set_param_value (char*,int) ; 
 char* strchr (char*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
handle_param (const char *carg)
{
  char *equal, *arg;
  int value;

  arg = xstrdup (carg);
  equal = strchr (arg, '=');
  if (!equal)
    error ("%s: --param arguments should be of the form NAME=VALUE", arg);
  else
    {
      value = integral_argument (equal + 1);
      if (value == -1)
	error ("invalid --param value %qs", equal + 1);
      else
	{
	  *equal = '\0';
	  set_param_value (arg, value);
	}
    }

  free (arg);
}