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
struct cref_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int FILECOL ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  cref_fill_array ; 
 int /*<<< orphan*/  cref_hash_traverse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cref_hash_entry***) ; 
 int /*<<< orphan*/  cref_initialized ; 
 int /*<<< orphan*/  cref_sort_array ; 
 int cref_symcount ; 
 int /*<<< orphan*/  cref_table ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  output_one_cref (int /*<<< orphan*/ *,struct cref_hash_entry*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qsort (struct cref_hash_entry**,int,int,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 struct cref_hash_entry** xmalloc (int) ; 

void
output_cref (FILE *fp)
{
  int len;
  struct cref_hash_entry **csyms, **csym_fill, **csym, **csym_end;
  const char *msg;

  fprintf (fp, _("\nCross Reference Table\n\n"));
  msg = _("Symbol");
  fprintf (fp, "%s", msg);
  len = strlen (msg);
  while (len < FILECOL)
    {
      putc (' ', fp);
      ++len;
    }
  fprintf (fp, _("File\n"));

  if (! cref_initialized)
    {
      fprintf (fp, _("No symbols\n"));
      return;
    }

  csyms = xmalloc (cref_symcount * sizeof (*csyms));

  csym_fill = csyms;
  cref_hash_traverse (&cref_table, cref_fill_array, &csym_fill);
  ASSERT ((size_t) (csym_fill - csyms) == cref_symcount);

  qsort (csyms, cref_symcount, sizeof (*csyms), cref_sort_array);

  csym_end = csyms + cref_symcount;
  for (csym = csyms; csym < csym_end; csym++)
    output_one_cref (fp, *csym);
}