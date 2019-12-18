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
struct dependency {int /*<<< orphan*/  file; struct dependency* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_WT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ column ; 
 struct dependency* dep_chain ; 
 int /*<<< orphan*/ * dep_file ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_file_name ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char) ; 

void
print_dependencies (void)
{
  FILE *f;
  struct dependency *dep;

  if (dep_file == NULL)
    return;

  f = fopen (dep_file, FOPEN_WT);
  if (f == NULL)
    {
      as_warn (_("can't open `%s' for writing"), dep_file);
      return;
    }

  column = 0;
  wrap_output (f, out_file_name, ':');
  for (dep = dep_chain; dep != NULL; dep = dep->next)
    wrap_output (f, dep->file, ' ');

  putc ('\n', f);

  if (fclose (f))
    as_warn (_("can't close `%s'"), dep_file);
}