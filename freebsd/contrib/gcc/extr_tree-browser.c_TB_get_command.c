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
typedef  unsigned int TB_CODE ;

/* Variables and functions */
 unsigned int TB_COMMAND_CODE (unsigned int) ; 
 unsigned int TB_COMMAND_LEN (unsigned int) ; 
 int /*<<< orphan*/  TB_COMMAND_TEXT (unsigned int) ; 
 unsigned int TB_UNUSED_COMMAND ; 
 int memcmp (char*,int /*<<< orphan*/ ,unsigned int) ; 
 char* strchr (char*,char) ; 
 unsigned int strlen (char*) ; 

__attribute__((used)) static TB_CODE
TB_get_command (char *input)
{
  unsigned int mn, size_tok;
  int comp;
  char *space;

  space = strchr (input, ' ');
  if (space != NULL)
    size_tok = strlen (input) - strlen (space);
  else
    size_tok = strlen (input) - 1;

  for (mn = 0; mn < TB_UNUSED_COMMAND; mn++)
    {
      if (size_tok != TB_COMMAND_LEN (mn))
	continue;

      comp = memcmp (input, TB_COMMAND_TEXT (mn), TB_COMMAND_LEN (mn));
      if (comp == 0)
	/* Here we just determined the command.  If this command takes
	   an argument, then the argument is determined later.  */
	return TB_COMMAND_CODE (mn);
    }

  /* Not a valid command.  */
  return TB_UNUSED_COMMAND;
}