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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_BASECLASS (struct type*,int) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 char* type_name_no_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
java_type_print_derivation_info (struct ui_file *stream, struct type *type)
{
  char *name;
  int i;
  int n_bases;
  int prev;

  n_bases = TYPE_N_BASECLASSES (type);

  for (i = 0, prev = 0; i < n_bases; i++)
    {
      int kind;

      kind = BASETYPE_VIA_VIRTUAL (type, i) ? 'I' : 'E';

      fputs_filtered (kind == prev ? ", "
		      : kind == 'I' ? " implements "
		      : " extends ",
		      stream);
      prev = kind;
      name = type_name_no_tag (TYPE_BASECLASS (type, i));

      fprintf_filtered (stream, "%s", name ? name : "(null)");
    }

  if (i > 0)
    fputs_filtered (" ", stream);
}