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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 unsigned int LAST_AND_UNUSED_TREE_CODE ; 
 int /*<<< orphan*/  TB_OUT_FILE ; 
 int TB_TREE_CODE (unsigned int) ; 
 unsigned int TB_TREE_CODE_LEN (unsigned int) ; 
 char* TB_TREE_CODE_TEXT (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int memcmp (char*,char*,unsigned int) ; 
 char* strchr (char*,char) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static enum tree_code
TB_get_tree_code (char *input)
{
  unsigned int mn, size_tok;
  int comp;
  char *space;

  space = strchr (input, ' ');
  if (space != NULL)
    size_tok = strlen (input) - strlen (space);
  else
    size_tok = strlen (input) - 1;

  for (mn = 0; mn < LAST_AND_UNUSED_TREE_CODE; mn++)
    {
      if (size_tok != TB_TREE_CODE_LEN (mn))
	continue;

      comp = memcmp (input, TB_TREE_CODE_TEXT (mn), TB_TREE_CODE_LEN (mn));
      if (comp == 0)
	{
	  fprintf (TB_OUT_FILE, "%s\n", TB_TREE_CODE_TEXT (mn));
	  return TB_TREE_CODE (mn);
	}
    }

  /* This isn't a valid code.  */
  return LAST_AND_UNUSED_TREE_CODE;
}