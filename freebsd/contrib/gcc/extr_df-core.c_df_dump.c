#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bitmap_size; } ;
struct TYPE_5__ {int bitmap_size; } ;
struct df {int num_problems_defined; TYPE_4__** problems_in_order; TYPE_2__ use_info; TYPE_1__ def_info; } ;
struct TYPE_8__ {TYPE_3__* problem; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* dump_fun ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* current_function_name () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 

void
df_dump (struct df *df, FILE *file)
{
  int i;

  if (!df || !file)
    return;

  fprintf (file, "\n\n%s\n", current_function_name ());
  fprintf (file, "\nDataflow summary:\n");
  fprintf (file, "def_info->bitmap_size = %d, use_info->bitmap_size = %d\n",
	   df->def_info.bitmap_size, df->use_info.bitmap_size);

  for (i = 0; i < df->num_problems_defined; i++)
    df->problems_in_order[i]->problem->dump_fun (df->problems_in_order[i], file); 

  fprintf (file, "\n");
}