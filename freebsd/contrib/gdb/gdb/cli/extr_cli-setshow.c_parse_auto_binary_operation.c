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
typedef  enum auto_boolean { ____Placeholder_auto_boolean } auto_boolean ;

/* Variables and functions */
 int AUTO_BOOLEAN_AUTO ; 
 int AUTO_BOOLEAN_FALSE ; 
 int AUTO_BOOLEAN_TRUE ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ isspace (char const) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static enum auto_boolean
parse_auto_binary_operation (const char *arg)
{
  if (arg != NULL && *arg != '\0')
    {
      int length = strlen (arg);
      while (isspace (arg[length - 1]) && length > 0)
	length--;
      if (strncmp (arg, "on", length) == 0
	  || strncmp (arg, "1", length) == 0
	  || strncmp (arg, "yes", length) == 0
	  || strncmp (arg, "enable", length) == 0)
	return AUTO_BOOLEAN_TRUE;
      else if (strncmp (arg, "off", length) == 0
	       || strncmp (arg, "0", length) == 0
	       || strncmp (arg, "no", length) == 0
	       || strncmp (arg, "disable", length) == 0)
	return AUTO_BOOLEAN_FALSE;
      else if (strncmp (arg, "auto", length) == 0
	       || (strncmp (arg, "-1", length) == 0 && length > 1))
	return AUTO_BOOLEAN_AUTO;
    }
  error ("\"on\", \"off\" or \"auto\" expected.");
  return AUTO_BOOLEAN_AUTO; /* pacify GCC */
}