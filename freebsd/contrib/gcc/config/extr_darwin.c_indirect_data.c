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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ TARGET_FIX_AND_CONTINUE ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int
indirect_data (rtx sym_ref)
{
  int lprefix;
  const char *name;

  /* If we aren't generating fix-and-continue code, don't do anything special.  */
  if (TARGET_FIX_AND_CONTINUE == 0)
    return 0;

  /* Otherwise, all symbol except symbols that begin with L or _OBJC_
     are indirected.  Symbols that begin with L and _OBJC_ are always
     bound to the current translation unit as they are used for
     generated local data of the translation unit.  */

  name = XSTR (sym_ref, 0);

  lprefix = (((name[0] == '*' || name[0] == '&')
              && (name[1] == 'L' || (name[1] == '"' && name[2] == 'L')))
             || (strncmp (name, "_OBJC_", 6) == 0));

  return ! lprefix;
}