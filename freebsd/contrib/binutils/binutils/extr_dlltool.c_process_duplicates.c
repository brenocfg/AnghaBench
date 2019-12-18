#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ordinal; int /*<<< orphan*/  noname; int /*<<< orphan*/  data; int /*<<< orphan*/  constant; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ export_type ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  d_named_nfuncs ; 
 int d_nfuncs ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nfunc ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_null_names (TYPE_1__**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_duplicates (export_type **d_export_vec)
{
  int more = 1;
  int i;

  while (more)
    {
      more = 0;
      /* Remove duplicates.  */
      qsort (d_export_vec, d_nfuncs, sizeof (export_type *), nfunc);

      for (i = 0; i < d_nfuncs - 1; i++)
	{
	  if (strcmp (d_export_vec[i]->name,
		      d_export_vec[i + 1]->name) == 0)
	    {
	      export_type *a = d_export_vec[i];
	      export_type *b = d_export_vec[i + 1];

	      more = 1;

	      /* xgettext:c-format */
	      inform (_("Warning, ignoring duplicate EXPORT %s %d,%d"),
		      a->name, a->ordinal, b->ordinal);

	      if (a->ordinal != -1
		  && b->ordinal != -1)
		/* xgettext:c-format */
		fatal (_("Error, duplicate EXPORT with oridinals: %s"),
		      a->name);

	      /* Merge attributes.  */
	      b->ordinal = a->ordinal > 0 ? a->ordinal : b->ordinal;
	      b->constant |= a->constant;
	      b->noname |= a->noname;
	      b->data |= a->data;
	      d_export_vec[i] = 0;
	    }

	  remove_null_names (d_export_vec);
	}
    }

  /* Count the names.  */
  for (i = 0; i < d_nfuncs; i++)
    if (!d_export_vec[i]->noname)
      d_named_nfuncs++;
}