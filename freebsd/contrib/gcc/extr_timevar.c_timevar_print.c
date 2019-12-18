#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t timevar_id_t ;
struct timevar_time_def {double const user; double const sys; double const wall; int ggc_mem; } ;
struct timevar_def {char* name; struct timevar_time_def elapsed; int /*<<< orphan*/  used; } ;
struct TYPE_4__ {TYPE_1__* timevar; } ;
struct TYPE_3__ {int /*<<< orphan*/  elapsed; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int GGC_MEM_BOUND ; 
 scalar_t__ TIMEVAR_LAST ; 
 size_t TV_TOTAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_time (struct timevar_time_def*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 TYPE_2__* stack ; 
 struct timevar_time_def start_time ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/  timevar_accumulate (int /*<<< orphan*/ *,struct timevar_time_def*,struct timevar_time_def*) ; 
 int /*<<< orphan*/  timevar_enable ; 
 struct timevar_def* timevars ; 

void
timevar_print (FILE *fp)
{
  /* Only print stuff if we have some sort of time information.  */
#if defined (HAVE_USER_TIME) || defined (HAVE_SYS_TIME) || defined (HAVE_WALL_TIME)
  unsigned int /* timevar_id_t */ id;
  struct timevar_time_def *total = &timevars[TV_TOTAL].elapsed;
  struct timevar_time_def now;

  if (!timevar_enable)
    return;

  /* Update timing information in case we're calling this from GDB.  */

  if (fp == 0)
    fp = stderr;

  /* What time is it?  */
  get_time (&now);

  /* If the stack isn't empty, attribute the current elapsed time to
     the old topmost element.  */
  if (stack)
    timevar_accumulate (&stack->timevar->elapsed, &start_time, &now);

  /* Reset the start time; from now on, time is attributed to
     TIMEVAR.  */
  start_time = now;

  fputs (_("\nExecution times (seconds)\n"), fp);
  for (id = 0; id < (unsigned int) TIMEVAR_LAST; ++id)
    {
      struct timevar_def *tv = &timevars[(timevar_id_t) id];
      const double tiny = 5e-3;

      /* Don't print the total execution time here; that goes at the
	 end.  */
      if ((timevar_id_t) id == TV_TOTAL)
	continue;

      /* Don't print timing variables that were never used.  */
      if (!tv->used)
	continue;

      /* Don't print timing variables if we're going to get a row of
         zeroes.  */
      if (tv->elapsed.user < tiny
	  && tv->elapsed.sys < tiny
	  && tv->elapsed.wall < tiny
	  && tv->elapsed.ggc_mem < GGC_MEM_BOUND)
	continue;

      /* The timing variable name.  */
      fprintf (fp, " %-22s:", tv->name);

#ifdef HAVE_USER_TIME
      /* Print user-mode time for this process.  */
      fprintf (fp, "%7.2f (%2.0f%%) usr",
	       tv->elapsed.user,
	       (total->user == 0 ? 0 : tv->elapsed.user / total->user) * 100);
#endif /* HAVE_USER_TIME */

#ifdef HAVE_SYS_TIME
      /* Print system-mode time for this process.  */
      fprintf (fp, "%7.2f (%2.0f%%) sys",
	       tv->elapsed.sys,
	       (total->sys == 0 ? 0 : tv->elapsed.sys / total->sys) * 100);
#endif /* HAVE_SYS_TIME */

#ifdef HAVE_WALL_TIME
      /* Print wall clock time elapsed.  */
      fprintf (fp, "%7.2f (%2.0f%%) wall",
	       tv->elapsed.wall,
	       (total->wall == 0 ? 0 : tv->elapsed.wall / total->wall) * 100);
#endif /* HAVE_WALL_TIME */

      /* Print the amount of ggc memory allocated.  */
      fprintf (fp, "%8u kB (%2.0f%%) ggc",
	       (unsigned) (tv->elapsed.ggc_mem >> 10),
	       (total->ggc_mem == 0
		? 0
		: (float) tv->elapsed.ggc_mem / total->ggc_mem) * 100);

      putc ('\n', fp);
    }

  /* Print total time.  */
  fputs (_(" TOTAL                 :"), fp);
#ifdef HAVE_USER_TIME
  fprintf (fp, "%7.2f          ", total->user);
#endif
#ifdef HAVE_SYS_TIME
  fprintf (fp, "%7.2f          ", total->sys);
#endif
#ifdef HAVE_WALL_TIME
  fprintf (fp, "%7.2f           ", total->wall);
#endif
  fprintf (fp, "%8u kB\n", (unsigned) (total->ggc_mem >> 10));

#ifdef ENABLE_CHECKING
  fprintf (fp, "Extra diagnostic checks enabled; compiler may run slowly.\n");
  fprintf (fp, "Configure with --disable-checking to disable checks.\n");
#endif

#endif /* defined (HAVE_USER_TIME) || defined (HAVE_SYS_TIME)
	  || defined (HAVE_WALL_TIME) */
}