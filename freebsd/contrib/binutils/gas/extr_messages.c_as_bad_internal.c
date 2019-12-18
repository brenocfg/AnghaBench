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
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identify (char*) ; 
 int /*<<< orphan*/  listing_error (char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
as_bad_internal (char *file, unsigned int line, char *buffer)
{
  ++error_count;

  if (file == NULL)
    as_where (&file, &line);

  identify (file);
  if (file)
    fprintf (stderr, "%s:%u: ", file, line);
  fprintf (stderr, _("Error: "));
  fputs (buffer, stderr);
  (void) putc ('\n', stderr);
#ifndef NO_LISTING
  listing_error (buffer);
#endif
}