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
struct ls_expr {int index; scalar_t__ stores; scalar_t__ loads; scalar_t__ pattern; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct ls_expr* first_ls_expr () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 struct ls_expr* next_ls_expr (struct ls_expr*) ; 
 int /*<<< orphan*/  print_rtl (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
print_ldst_list (FILE * file)
{
  struct ls_expr * ptr;

  fprintf (file, "LDST list: \n");

  for (ptr = first_ls_expr(); ptr != NULL; ptr = next_ls_expr (ptr))
    {
      fprintf (file, "  Pattern (%3d): ", ptr->index);

      print_rtl (file, ptr->pattern);

      fprintf (file, "\n	 Loads : ");

      if (ptr->loads)
	print_rtl (file, ptr->loads);
      else
	fprintf (file, "(nil)");

      fprintf (file, "\n	Stores : ");

      if (ptr->stores)
	print_rtl (file, ptr->stores);
      else
	fprintf (file, "(nil)");

      fprintf (file, "\n\n");
    }

  fprintf (file, "\n");
}