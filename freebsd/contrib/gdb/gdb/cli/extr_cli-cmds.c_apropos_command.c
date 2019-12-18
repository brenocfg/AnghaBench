#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cmd_list_element {int dummy; } ;
struct TYPE_5__ {char* fastmap; } ;
typedef  TYPE_1__ regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ICASE ; 
 int /*<<< orphan*/  apropos_cmd (int /*<<< orphan*/ ,struct cmd_list_element*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  re_compile_fastmap (TYPE_1__*) ; 
 scalar_t__ regcomp (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regerror (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 char* xcalloc (int,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void 
apropos_command (char *searchstr, int from_tty)
{
  extern struct cmd_list_element *cmdlist; /*This is the main command list*/
  regex_t pattern;
  char *pattern_fastmap;
  char errorbuffer[512];
  pattern_fastmap = xcalloc (256, sizeof (char));
  if (searchstr == NULL)
      error("REGEXP string is empty");

  if (regcomp(&pattern,searchstr,REG_ICASE) == 0)
    {
      pattern.fastmap=pattern_fastmap;
      re_compile_fastmap(&pattern);
      apropos_cmd (gdb_stdout,cmdlist,&pattern,"");
    }
  else
    {
      regerror(regcomp(&pattern,searchstr,REG_ICASE),NULL,errorbuffer,512);
      error("Error in regular expression:%s",errorbuffer);
    }
  xfree (pattern_fastmap);
}