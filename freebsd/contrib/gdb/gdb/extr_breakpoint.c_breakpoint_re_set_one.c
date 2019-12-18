#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct symtabs_and_lines {int nelts; TYPE_3__* sals; } ;
struct symtab {int dummy; } ;
struct breakpoint {int type; char* addr_string; int enable_state; char* cond_string; TYPE_3__* cond; int /*<<< orphan*/ * val; TYPE_3__* exp; int /*<<< orphan*/ * exp_valid_block; int /*<<< orphan*/  exp_string; TYPE_2__* loc; int /*<<< orphan*/  line_number; TYPE_3__* source_file; int /*<<< orphan*/  input_radix; int /*<<< orphan*/  language; int /*<<< orphan*/  pending; int /*<<< orphan*/  number; } ;
struct block {int dummy; } ;
typedef  enum enable_state { ____Placeholder_enable_state } enable_state ;
struct TYPE_11__ {int /*<<< orphan*/  section; int /*<<< orphan*/  pc; int /*<<< orphan*/  line; TYPE_1__* symtab; } ;
struct TYPE_10__ {int /*<<< orphan*/  section; int /*<<< orphan*/  requested_address; int /*<<< orphan*/  address; } ;
struct TYPE_9__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_LAZY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adjust_breakpoint_address (int /*<<< orphan*/ ) ; 
 struct block* block_for_pc (int /*<<< orphan*/ ) ; 
#define  bp_access_watchpoint 151 
#define  bp_breakpoint 150 
#define  bp_call_dummy 149 
#define  bp_catch_catch 148 
#define  bp_catch_exec 147 
#define  bp_catch_fork 146 
#define  bp_catch_load 145 
#define  bp_catch_throw 144 
#define  bp_catch_unload 143 
#define  bp_catch_vfork 142 
 int bp_disabled ; 
#define  bp_finish 141 
#define  bp_hardware_breakpoint 140 
#define  bp_hardware_watchpoint 139 
#define  bp_longjmp 138 
#define  bp_longjmp_resume 137 
#define  bp_none 136 
#define  bp_overlay_event 135 
#define  bp_read_watchpoint 134 
 int bp_shlib_disabled ; 
#define  bp_shlib_event 133 
#define  bp_step_resume 132 
#define  bp_thread_event 131 
#define  bp_until 130 
#define  bp_watchpoint 129 
#define  bp_watchpoint_scope 128 
 int /*<<< orphan*/  breakpoint_enabled (struct breakpoint*) ; 
 int /*<<< orphan*/  breakpoints_changed () ; 
 int /*<<< orphan*/  check_duplicates (struct breakpoint*) ; 
 struct symtabs_and_lines decode_line_1 (char**,int,struct symtab*,int /*<<< orphan*/ ,char***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_breakpoint (struct breakpoint*) ; 
 int /*<<< orphan*/ * evaluate_expression (TYPE_3__*) ; 
 int /*<<< orphan*/ * innermost_block ; 
 int /*<<< orphan*/  input_radix ; 
 int /*<<< orphan*/  mention (struct breakpoint*) ; 
 void* parse_exp_1 (char**,struct block*,int /*<<< orphan*/ ) ; 
 TYPE_3__* parse_expression (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,int) ; 
 int /*<<< orphan*/  release_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_sal_pc (TYPE_3__*) ; 
 TYPE_3__* savestring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_language (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_fetch_lazy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_free_to_mark (struct value*) ; 
 struct value* value_mark () ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (TYPE_3__*) ; 

__attribute__((used)) static int
breakpoint_re_set_one (void *bint)
{
  /* get past catch_errs */
  struct breakpoint *b = (struct breakpoint *) bint;
  struct value *mark;
  int i;
  struct symtabs_and_lines sals;
  char *s;
  enum enable_state save_enable;

  switch (b->type)
    {
    case bp_none:
      warning ("attempted to reset apparently deleted breakpoint #%d?",
	       b->number);
      return 0;
    case bp_breakpoint:
    case bp_hardware_breakpoint:
    case bp_catch_load:
    case bp_catch_unload:
      if (b->addr_string == NULL)
	{
	  /* Anything without a string can't be re-set. */
	  delete_breakpoint (b);
	  return 0;
	}
      /* HACK: cagney/2001-11-11: kettenis/2001-11-11: MarkK wrote:

	 ``And a hack it is, although Apple's Darwin version of GDB
	 contains an almost identical hack to implement a "future
	 break" command.  It seems to work in many real world cases,
	 but it is easy to come up with a test case where the patch
	 doesn't help at all.''

	 ``It seems that the way GDB implements breakpoints - in -
	 shared - libraries was designed for a.out shared library
	 systems (SunOS 4) where shared libraries were loaded at a
	 fixed address in memory.  Since ELF shared libraries can (and
	 will) be loaded at any address in memory, things break.
	 Fixing this is not trivial.  Therefore, I'm not sure whether
	 we should add this hack to the branch only.  I cannot
	 guarantee that things will be fixed on the trunk in the near
	 future.''

         In case we have a problem, disable this breakpoint.  We'll
         restore its status if we succeed.  Don't disable a
         shlib_disabled breakpoint though.  There's a fair chance we
         can't re-set it if the shared library it's in hasn't been
         loaded yet.  */

      if (b->pending)
	break;

      save_enable = b->enable_state;
      if (b->enable_state != bp_shlib_disabled)
        b->enable_state = bp_disabled;

      set_language (b->language);
      input_radix = b->input_radix;
      s = b->addr_string;
      sals = decode_line_1 (&s, 1, (struct symtab *) NULL, 0, (char ***) NULL, NULL);
      for (i = 0; i < sals.nelts; i++)
	{
	  resolve_sal_pc (&sals.sals[i]);

	  /* Reparse conditions, they might contain references to the
	     old symtab.  */
	  if (b->cond_string != NULL)
	    {
	      s = b->cond_string;
	      if (b->cond)
		{
		  xfree (b->cond);
		  /* Avoid re-freeing b->exp if an error during the call
		     to parse_exp_1.  */
		  b->cond = NULL;
		}
	      b->cond = parse_exp_1 (&s, block_for_pc (sals.sals[i].pc), 0);
	    }

	  /* We need to re-set the breakpoint if the address changes... */
	  if (b->loc->address != sals.sals[i].pc
	  /* ...or new and old breakpoints both have source files, and
	     the source file name or the line number changes...  */
	      || (b->source_file != NULL
		  && sals.sals[i].symtab != NULL
		  && (strcmp (b->source_file, sals.sals[i].symtab->filename) != 0
		      || b->line_number != sals.sals[i].line)
	      )
	  /* ...or we switch between having a source file and not having
	     one.  */
	      || ((b->source_file == NULL) != (sals.sals[i].symtab == NULL))
	    )
	    {
	      if (b->source_file != NULL)
		xfree (b->source_file);
	      if (sals.sals[i].symtab == NULL)
		b->source_file = NULL;
	      else
		b->source_file =
		  savestring (sals.sals[i].symtab->filename,
			      strlen (sals.sals[i].symtab->filename));
	      b->line_number = sals.sals[i].line;
	      b->loc->requested_address = sals.sals[i].pc;
	      b->loc->address
	        = adjust_breakpoint_address (b->loc->requested_address);

	      /* Used to check for duplicates here, but that can
	         cause trouble, as it doesn't check for disabled
	         breakpoints. */

	      mention (b);

	      /* Might be better to do this just once per breakpoint_re_set,
	         rather than once for every breakpoint.  */
	      breakpoints_changed ();
	    }
	  b->loc->section = sals.sals[i].section;
	  b->enable_state = save_enable;	/* Restore it, this worked. */


	  /* Now that this is re-enabled, check_duplicates
	     can be used. */
	  check_duplicates (b);

	}
      xfree (sals.sals);
      break;

    case bp_watchpoint:
    case bp_hardware_watchpoint:
    case bp_read_watchpoint:
    case bp_access_watchpoint:
      innermost_block = NULL;
      /* The issue arises of what context to evaluate this in.  The
         same one as when it was set, but what does that mean when
         symbols have been re-read?  We could save the filename and
         functionname, but if the context is more local than that, the
         best we could do would be something like how many levels deep
         and which index at that particular level, but that's going to
         be less stable than filenames or function names.  */

      /* So for now, just use a global context.  */
      if (b->exp)
	{
	  xfree (b->exp);
	  /* Avoid re-freeing b->exp if an error during the call to
             parse_expression.  */
	  b->exp = NULL;
	}
      b->exp = parse_expression (b->exp_string);
      b->exp_valid_block = innermost_block;
      mark = value_mark ();
      if (b->val)
	{
	  value_free (b->val);
	  /* Avoid re-freeing b->val if an error during the call to
             evaluate_expression.  */
	  b->val = NULL;
	}
      b->val = evaluate_expression (b->exp);
      release_value (b->val);
      if (VALUE_LAZY (b->val) && breakpoint_enabled (b))
	value_fetch_lazy (b->val);

      if (b->cond_string != NULL)
	{
	  s = b->cond_string;
	  if (b->cond)
	    {
	      xfree (b->cond);
	      /* Avoid re-freeing b->exp if an error during the call
		 to parse_exp_1.  */
	      b->cond = NULL;
	    }
	  b->cond = parse_exp_1 (&s, (struct block *) 0, 0);
	}
      if (breakpoint_enabled (b))
	mention (b);
      value_free_to_mark (mark);
      break;
    case bp_catch_catch:
    case bp_catch_throw:
      break;
      /* We needn't really do anything to reset these, since the mask
         that requests them is unaffected by e.g., new libraries being
         loaded. */
    case bp_catch_fork:
    case bp_catch_vfork:
    case bp_catch_exec:
      break;

    default:
      printf_filtered ("Deleting unknown breakpoint type %d\n", b->type);
      /* fall through */
      /* Delete longjmp and overlay event breakpoints; they will be
         reset later by breakpoint_re_set.  */
    case bp_longjmp:
    case bp_longjmp_resume:
    case bp_overlay_event:
      delete_breakpoint (b);
      break;

      /* This breakpoint is special, it's set up when the inferior
         starts and we really don't want to touch it.  */
    case bp_shlib_event:

      /* Like bp_shlib_event, this breakpoint type is special.
	 Once it is set up, we do not want to touch it.  */
    case bp_thread_event:

      /* Keep temporary breakpoints, which can be encountered when we step
         over a dlopen call and SOLIB_ADD is resetting the breakpoints.
         Otherwise these should have been blown away via the cleanup chain
         or by breakpoint_init_inferior when we rerun the executable.  */
    case bp_until:
    case bp_finish:
    case bp_watchpoint_scope:
    case bp_call_dummy:
    case bp_step_resume:
      break;
    }

  return 0;
}