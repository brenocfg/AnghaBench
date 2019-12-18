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
struct ui_file {int dummy; } ;
struct symtabs_and_lines {int dummy; } ;
struct symtab_and_line {int dummy; } ;
struct lang_and_radix {int /*<<< orphan*/  radix; int /*<<< orphan*/  lang; } ;
struct cleanup {int dummy; } ;
struct breakpoint {char* addr_string; int /*<<< orphan*/  from_tty; int /*<<< orphan*/  flag; int /*<<< orphan*/  input_radix; int /*<<< orphan*/  language; } ;
struct TYPE_2__ {int /*<<< orphan*/  la_language; } ;

/* Variables and functions */
 int GDB_RC_OK ; 
 int break_command_1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct breakpoint*) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_restore_lang_radix_cleanup ; 
 int /*<<< orphan*/  input_radix ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct lang_and_radix*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*) ; 
 int /*<<< orphan*/  set_language (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
resolve_pending_breakpoint (struct breakpoint *b)
{
  /* Try and reparse the breakpoint in case the shared library
     is now loaded.  */
  struct symtabs_and_lines sals;
  struct symtab_and_line pending_sal;
  char **cond_string = (char **) NULL;
  char *copy_arg = b->addr_string;
  char **addr_string;
  char *errmsg;
  int rc;
  int not_found = 0;
  struct ui_file *old_gdb_stderr;
  struct lang_and_radix old_lr;
  struct cleanup *old_chain;
  
  /* Set language, input-radix, then reissue breakpoint command. 
     Ensure the language and input-radix are restored afterwards.  */
  old_lr.lang = current_language->la_language;
  old_lr.radix = input_radix;
  old_chain = make_cleanup (do_restore_lang_radix_cleanup, &old_lr);
  
  set_language (b->language);
  input_radix = b->input_radix;
  rc = break_command_1 (b->addr_string, b->flag, b->from_tty, b);
  
  if (rc == GDB_RC_OK)
    /* Pending breakpoint has been resolved.  */
    printf_filtered ("Pending breakpoint \"%s\" resolved\n", b->addr_string);

  do_cleanups (old_chain);
  return rc;
}