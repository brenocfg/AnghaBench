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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int IDENTIFIER_LENGTH (int /*<<< orphan*/ ) ; 
 scalar_t__ IDENTIFIER_NODE ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int
is_attribute_with_length_p (const char *attr, int attr_len, tree ident)
{
  int ident_len;
  const char *p;

  if (TREE_CODE (ident) != IDENTIFIER_NODE)
    return 0;
  
  p = IDENTIFIER_POINTER (ident);
  ident_len = IDENTIFIER_LENGTH (ident);
  
  if (ident_len == attr_len
      && strcmp (attr, p) == 0)
    return 1;

  /* If ATTR is `__text__', IDENT must be `text'; and vice versa.  */
  if (attr[0] == '_')
    {
      gcc_assert (attr[1] == '_');
      gcc_assert (attr[attr_len - 2] == '_');
      gcc_assert (attr[attr_len - 1] == '_');
      if (ident_len == attr_len - 4
	  && strncmp (attr + 2, p, attr_len - 4) == 0)
	return 1;
    }
  else
    {
      if (ident_len == attr_len + 4
	  && p[0] == '_' && p[1] == '_'
	  && p[ident_len - 2] == '_' && p[ident_len - 1] == '_'
	  && strncmp (attr, p + 2, attr_len) == 0)
	return 1;
    }

  return 0;
}