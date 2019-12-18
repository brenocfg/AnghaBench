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
 int /*<<< orphan*/ * strchr (char const*,char const) ; 

__attribute__((used)) static int 
is_objc_method_format (const char *s)
{
  if (s == NULL || *s == '\0')
    return 0;
  /* Handle arguments with the format FILENAME:SYMBOL.  */
  if ((s[0] == ':') && (strchr ("+-", s[1]) != NULL) 
      && (s[2] == '[') && strchr(s, ']'))
    return 1;
  /* Handle arguments that are just SYMBOL.  */
  else if ((strchr ("+-", s[0]) != NULL) && (s[1] == '[') && strchr(s, ']'))
    return 1;
  return 0;
}