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
 char* _ (char*) ; 
 int /*<<< orphan*/  as_where (char**,unsigned int*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identify (char*) ; 
 int /*<<< orphan*/  listing_warning (char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warning_count ; 

__attribute__((used)) static void
as_warn_internal (char *file, unsigned int line, char *buffer)
{
  ++warning_count;

  if (file == NULL)
    as_where (&file, &line);

  identify (file);
  if (file)
    fprintf (stderr, "%s:%u: ", file, line);
  fprintf (stderr, _("Warning: "));
  fputs (buffer, stderr);
  (void) putc ('\n', stderr);
#ifndef NO_LISTING
  listing_warning (buffer);
#endif
}