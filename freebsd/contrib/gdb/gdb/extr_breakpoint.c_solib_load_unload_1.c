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
struct symtabs_and_lines {int nelts; char* sals; } ;
struct symtab {int dummy; } ;
struct cleanup {int dummy; } ;
struct breakpoint {char* cond_string; int thread; char* addr_string; char* dll_pathname; int /*<<< orphan*/  disposition; int /*<<< orphan*/  enable_state; int /*<<< orphan*/ * cond; scalar_t__ number; } ;
typedef  enum bptype { ____Placeholder_bptype } bptype ;

/* Variables and functions */
 int /*<<< orphan*/  bp_enabled ; 
 scalar_t__ breakpoint_count ; 
 struct symtabs_and_lines decode_line_1 (char**,int,struct symtab*,int /*<<< orphan*/ ,char***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  disp_del ; 
 int /*<<< orphan*/  disp_donttouch ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mention (struct breakpoint*) ; 
 int /*<<< orphan*/  null_cleanup ; 
 int /*<<< orphan*/  resolve_sal_pc (char*) ; 
 char* savestring (char*,int) ; 
 int /*<<< orphan*/  set_breakpoint_count (scalar_t__) ; 
 struct breakpoint* set_raw_breakpoint (char,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
solib_load_unload_1 (char *hookname, int tempflag, char *dll_pathname,
		     char *cond_string, enum bptype bp_kind)
{
  struct breakpoint *b;
  struct symtabs_and_lines sals;
  struct cleanup *old_chain;
  struct cleanup *canonical_strings_chain = NULL;
  char *addr_start = hookname;
  char *addr_end = NULL;
  char **canonical = (char **) NULL;
  int thread = -1;		/* All threads. */

  /* Set a breakpoint on the specified hook. */
  sals = decode_line_1 (&hookname, 1, (struct symtab *) NULL, 0, &canonical, NULL);
  addr_end = hookname;

  if (sals.nelts == 0)
    {
      warning ("Unable to set a breakpoint on dynamic linker callback.");
      warning ("Suggest linking with /opt/langtools/lib/end.o.");
      warning ("GDB will be unable to track shl_load/shl_unload calls");
      return;
    }
  if (sals.nelts != 1)
    {
      warning ("Unable to set unique breakpoint on dynamic linker callback.");
      warning ("GDB will be unable to track shl_load/shl_unload calls");
      return;
    }

  /* Make sure that all storage allocated in decode_line_1 gets freed
     in case the following errors out.  */
  old_chain = make_cleanup (xfree, sals.sals);
  if (canonical != (char **) NULL)
    {
      make_cleanup (xfree, canonical);
      canonical_strings_chain = make_cleanup (null_cleanup, 0);
      if (canonical[0] != NULL)
	make_cleanup (xfree, canonical[0]);
    }

  resolve_sal_pc (&sals.sals[0]);

  /* Remove the canonical strings from the cleanup, they are needed below.  */
  if (canonical != (char **) NULL)
    discard_cleanups (canonical_strings_chain);

  b = set_raw_breakpoint (sals.sals[0], bp_kind);
  set_breakpoint_count (breakpoint_count + 1);
  b->number = breakpoint_count;
  b->cond = NULL;
  b->cond_string = (cond_string == NULL) ? 
    NULL : savestring (cond_string, strlen (cond_string));
  b->thread = thread;

  if (canonical != (char **) NULL && canonical[0] != NULL)
    b->addr_string = canonical[0];
  else if (addr_start)
    b->addr_string = savestring (addr_start, addr_end - addr_start);

  b->enable_state = bp_enabled;
  b->disposition = tempflag ? disp_del : disp_donttouch;

  if (dll_pathname == NULL)
    b->dll_pathname = NULL;
  else
    {
      b->dll_pathname = (char *) xmalloc (strlen (dll_pathname) + 1);
      strcpy (b->dll_pathname, dll_pathname);
    }

  mention (b);
  do_cleanups (old_chain);
}