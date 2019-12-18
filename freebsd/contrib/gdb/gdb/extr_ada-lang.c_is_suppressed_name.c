#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char const* mangled; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_STREQN (char const*,char const*,int) ; 
 TYPE_1__* ada_opname_table ; 
 scalar_t__ isupper (char const) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int
is_suppressed_name (const char *str)
{
  if (DEPRECATED_STREQN (str, "_ada_", 5))
    str += 5;
  if (str[0] == '_' || str[0] == '\000')
    return 1;
  else
    {
      const char *p;
      const char *suffix = strstr (str, "___");
      if (suffix != NULL && suffix[3] != 'X')
	return 1;
      if (suffix == NULL)
	suffix = str + strlen (str);
      for (p = suffix - 1; p != str; p -= 1)
	if (isupper (*p))
	  {
	    int i;
	    if (p[0] == 'X' && p[-1] != '_')
	      goto OK;
	    if (*p != 'O')
	      return 1;
	    for (i = 0; ada_opname_table[i].mangled != NULL; i += 1)
	      if (DEPRECATED_STREQN (ada_opname_table[i].mangled, p,
			  strlen (ada_opname_table[i].mangled)))
		goto OK;
	    return 1;
	  OK:;
	  }
      return 0;
    }
}