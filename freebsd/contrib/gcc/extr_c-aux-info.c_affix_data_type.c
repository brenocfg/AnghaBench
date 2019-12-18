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
 char* ASTRDUP (char const*) ; 
 char* concat (char* const,char*,char* const,...) ; 
 int /*<<< orphan*/  data_type ; 
 char* reconcat (char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static char *
affix_data_type (const char *param)
{
  char *const type_or_decl = ASTRDUP (param);
  char *p = type_or_decl;
  char *qualifiers_then_data_type;
  char saved;

  /* Skip as many leading const's or volatile's as there are.  */

  for (;;)
    {
      if (!strncmp (p, "volatile ", 9))
	{
	  p += 9;
	  continue;
	}
      if (!strncmp (p, "const ", 6))
	{
	  p += 6;
	  continue;
	}
      break;
    }

  /* p now points to the place where we can insert the data type.  We have to
     add a blank after the data-type of course.  */

  if (p == type_or_decl)
    return concat (data_type, " ", type_or_decl, NULL);

  saved = *p;
  *p = '\0';
  qualifiers_then_data_type = concat (type_or_decl, data_type, NULL);
  *p = saved;
  return reconcat (qualifiers_then_data_type,
		   qualifiers_then_data_type, " ", p, NULL);
}