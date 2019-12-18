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
 int ISDIGIT (char const) ; 
 char* default_strip_name_encoding (char const*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 char* ggc_alloc_string (char const*,int) ; 
 char* strchr (char const*,char) ; 

const char *
i386_nlm_strip_name_encoding (const char *str)
{
  const char *name = default_strip_name_encoding (str);

  if (*str != '*' && (*name == '_' || *name == '@'))
    {
      const char *p = strchr (name + 1, '@');

      if (p)
	{
	  ++name;
	  if (ISDIGIT (p[1]))
	    name = ggc_alloc_string (name, p - name);
	  else
	    {
	      gcc_assert (ISDIGIT (*name));
	      name++;
	      gcc_assert (name == p);
	    }
	}
    }
  return name;
}