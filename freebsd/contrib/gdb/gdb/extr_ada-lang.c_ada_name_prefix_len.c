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
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

int
ada_name_prefix_len (const char *name)
{
  if (name == NULL)
    return 0;
  else
    {
      const char *p = strstr (name, "___");
      if (p == NULL)
	return strlen (name);
      else
	return p - name;
    }
}