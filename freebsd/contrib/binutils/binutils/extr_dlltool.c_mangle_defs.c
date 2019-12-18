#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hint; int /*<<< orphan*/  noname; struct TYPE_8__* next; } ;
typedef  TYPE_1__ export_type ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_1__* d_exports ; 
 TYPE_1__** d_exports_lexically ; 
 int d_nfuncs ; 
 int /*<<< orphan*/  fill_ordinals (TYPE_1__**) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfunc ; 
 int /*<<< orphan*/  process_duplicates (TYPE_1__**) ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ show_allnames ; 
 TYPE_1__** xmalloc (int) ; 

__attribute__((used)) static void
mangle_defs (void)
{
  /* First work out the minimum ordinal chosen.  */
  export_type *exp;

  int i;
  int hint = 0;
  export_type **d_export_vec = xmalloc (sizeof (export_type *) * d_nfuncs);

  inform (_("Processing definitions"));

  for (i = 0, exp = d_exports; exp; i++, exp = exp->next)
    d_export_vec[i] = exp;

  process_duplicates (d_export_vec);
  fill_ordinals (d_export_vec);

  /* Put back the list in the new order.  */
  d_exports = 0;
  for (i = d_nfuncs - 1; i >= 0; i--)
    {
      d_export_vec[i]->next = d_exports;
      d_exports = d_export_vec[i];
    }

  /* Build list in alpha order.  */
  d_exports_lexically = (export_type **)
    xmalloc (sizeof (export_type *) * (d_nfuncs + 1));

  for (i = 0, exp = d_exports; exp; i++, exp = exp->next)
    d_exports_lexically[i] = exp;

  d_exports_lexically[i] = 0;

  qsort (d_exports_lexically, i, sizeof (export_type *), nfunc);

  /* Fill exp entries with their hint values.  */
  for (i = 0; i < d_nfuncs; i++)
    if (!d_exports_lexically[i]->noname || show_allnames)
      d_exports_lexically[i]->hint = hint++;

  inform (_("Processed definitions"));
}