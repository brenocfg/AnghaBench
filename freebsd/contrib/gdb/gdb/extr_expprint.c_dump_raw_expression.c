#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union exp_element {int dummy; } exp_element ;
struct ui_file {int dummy; } ;
struct expression {int nelts; TYPE_2__* elts; TYPE_1__* language_defn; } ;
struct TYPE_4__ {int /*<<< orphan*/  longconst; int /*<<< orphan*/  opcode; } ;
struct TYPE_3__ {int /*<<< orphan*/  la_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  gdb_print_host_address (struct expression*,struct ui_file*) ; 
 scalar_t__ isprint (char) ; 
 char* op_name (struct expression*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dump_raw_expression (struct expression *exp, struct ui_file *stream,
		     char *note)
{
  int elt;
  char *opcode_name;
  char *eltscan;
  int eltsize;

  fprintf_filtered (stream, "Dump of expression @ ");
  gdb_print_host_address (exp, stream);
  fprintf_filtered (stream, "'\n\tLanguage %s, %d elements, %ld bytes each.\n",
		    exp->language_defn->la_name, exp->nelts,
		    (long) sizeof (union exp_element));
  fprintf_filtered (stream, "\t%5s  %20s  %16s  %s\n", "Index", "Opcode",
		    "Hex Value", "String Value");
  for (elt = 0; elt < exp->nelts; elt++)
    {
      fprintf_filtered (stream, "\t%5d  ", elt);
      opcode_name = op_name (exp, exp->elts[elt].opcode);

      fprintf_filtered (stream, "%20s  ", opcode_name);
      print_longest (stream, 'd', 0, exp->elts[elt].longconst);
      fprintf_filtered (stream, "  ");

      for (eltscan = (char *) &exp->elts[elt],
	   eltsize = sizeof (union exp_element);
	   eltsize-- > 0;
	   eltscan++)
	{
	  fprintf_filtered (stream, "%c",
			    isprint (*eltscan) ? (*eltscan & 0xFF) : '.');
	}
      fprintf_filtered (stream, "\n");
    }
}