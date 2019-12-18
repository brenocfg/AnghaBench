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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_RT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * fopen (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * yyin ; 
 int /*<<< orphan*/  yyparse () ; 

__attribute__((used)) static void
process_def_file (const char *name)
{
  FILE *f = fopen (name, FOPEN_RT);

  if (!f)
    /* xgettext:c-format */
    fatal (_("Can't open def file: %s"), name);

  yyin = f;

  /* xgettext:c-format */
  inform (_("Processing def file: %s"), name);

  yyparse ();

  inform (_("Processed def file"));
}