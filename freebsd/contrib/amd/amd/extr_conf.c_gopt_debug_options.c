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

/* Variables and functions */
 char* am_get_progname () ; 
 scalar_t__ debug_option (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage ; 

__attribute__((used)) static int
gopt_debug_options(const char *val)
{
#ifdef DEBUG
  usage += debug_option((char *)val);
  return 0;
#else /* not DEBUG */
  fprintf(stderr, "%s: not compiled with DEBUG option -- sorry.\n",
	  am_get_progname());
  return 1;
#endif /* not DEBUG */
}