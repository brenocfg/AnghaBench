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
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
strip_bg_char (char **args)
{
  char *p = NULL;

  p = strchr (*args, '&');

  if (p)
    {
      if (p == (*args + strlen (*args) - 1))
	{
	  if (strlen (*args) > 1)
	    {
	      do
		p--;
	      while (*p == ' ' || *p == '\t');
	      *(p + 1) = '\0';
	    }
	  else
	    *args = 0;
	  return 1;
	}
    }
  return 0;
}