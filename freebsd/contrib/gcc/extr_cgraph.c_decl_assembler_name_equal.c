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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ DECL_ASSEMBLER_NAME (scalar_t__) ; 
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  user_label_prefix ; 

__attribute__((used)) static bool
decl_assembler_name_equal (tree decl, tree asmname)
{
  tree decl_asmname = DECL_ASSEMBLER_NAME (decl);

  if (decl_asmname == asmname)
    return true;

  /* If the target assembler name was set by the user, things are trickier.
     We have a leading '*' to begin with.  After that, it's arguable what
     is the correct thing to do with -fleading-underscore.  Arguably, we've
     historically been doing the wrong thing in assemble_alias by always
     printing the leading underscore.  Since we're not changing that, make
     sure user_label_prefix follows the '*' before matching.  */
  if (IDENTIFIER_POINTER (decl_asmname)[0] == '*')
    {
      const char *decl_str = IDENTIFIER_POINTER (decl_asmname) + 1;
      size_t ulp_len = strlen (user_label_prefix);

      if (ulp_len == 0)
	;
      else if (strncmp (decl_str, user_label_prefix, ulp_len) == 0)
	decl_str += ulp_len;
      else
	return false;

      return strcmp (decl_str, IDENTIFIER_POINTER (asmname)) == 0;
    }

  return false;
}