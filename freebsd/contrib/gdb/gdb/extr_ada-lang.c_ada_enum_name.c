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
 scalar_t__ isascii (int) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int sscanf (char const*,char*,int*) ; 
 char* strchr (char const*,char) ; 
 char* strstr (char const*,char*) ; 

const char *
ada_enum_name (const char *name)
{
  char *tmp;

  while (1)
    {
      if ((tmp = strstr (name, "__")) != NULL)
	name = tmp + 2;
      else if ((tmp = strchr (name, '.')) != NULL)
	name = tmp + 1;
      else
	break;
    }

  if (name[0] == 'Q')
    {
      static char result[16];
      int v;
      if (name[1] == 'U' || name[1] == 'W')
	{
	  if (sscanf (name + 2, "%x", &v) != 1)
	    return name;
	}
      else
	return name;

      if (isascii (v) && isprint (v))
	sprintf (result, "'%c'", v);
      else if (name[1] == 'U')
	sprintf (result, "[\"%02x\"]", v);
      else
	sprintf (result, "[\"%04x\"]", v);

      return result;
    }
  else
    return name;
}