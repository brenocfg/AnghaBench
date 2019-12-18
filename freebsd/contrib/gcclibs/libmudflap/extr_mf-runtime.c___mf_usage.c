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
struct option {char* name; scalar_t__ value; scalar_t__* target; int type; char* description; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct option* options ; 
 scalar_t__ pthread_join ; 
#define  read_integer_option 129 
#define  set_option 128 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static void
__mf_usage ()
{
  struct option *opt;

  fprintf (stderr,
           "This is a %s%sGCC \"mudflap\" memory-checked binary.\n"
           "Mudflap is Copyright (C) 2002-2004 Free Software Foundation, Inc.\n"
           "\n"
           "The mudflap code can be controlled by an environment variable:\n"
           "\n"
           "$ export MUDFLAP_OPTIONS='<options>'\n"
           "$ <mudflapped_program>\n"
           "\n"
           "where <options> is a space-separated list of \n"
           "any of the following options.  Use `-no-OPTION' to disable options.\n"
           "\n",
#if HAVE_PTHREAD_H
           (pthread_join ? "multi-threaded " : "single-threaded "),
#else
           "",
#endif
#if LIBMUDFLAPTH
           "thread-aware "
#else
           "thread-unaware "
#endif
            );
  /* XXX: The multi-threaded thread-unaware combination is bad.  */

  for (opt = options; opt->name; opt++)
    {
      int default_p = (opt->value == * opt->target);

      switch (opt->type)
        {
          char buf[128];
        case set_option:
          fprintf (stderr, "-%-23.23s %s", opt->name, opt->description);
          if (default_p)
            fprintf (stderr, " [active]\n");
          else
            fprintf (stderr, "\n");
          break;
        case read_integer_option:
          strncpy (buf, opt->name, 128);
          strncpy (buf + strlen (opt->name), "=N", 2);
          fprintf (stderr, "-%-23.23s %s", buf, opt->description);
          fprintf (stderr, " [%d]\n", * opt->target);
          break;
        default: abort();
        }
    }

  fprintf (stderr, "\n");
}