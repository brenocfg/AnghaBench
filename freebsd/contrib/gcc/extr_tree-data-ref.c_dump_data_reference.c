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
struct data_reference {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DR_ACCESS_FN (struct data_reference*,unsigned int) ; 
 int /*<<< orphan*/  DR_BASE_OBJECT (struct data_reference*) ; 
 unsigned int DR_NUM_DIMENSIONS (struct data_reference*) ; 
 int /*<<< orphan*/  DR_REF (struct data_reference*) ; 
 int /*<<< orphan*/  DR_STMT (struct data_reference*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_generic_stmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
dump_data_reference (FILE *outf, 
		     struct data_reference *dr)
{
  unsigned int i;
  
  fprintf (outf, "(Data Ref: \n  stmt: ");
  print_generic_stmt (outf, DR_STMT (dr), 0);
  fprintf (outf, "  ref: ");
  print_generic_stmt (outf, DR_REF (dr), 0);
  fprintf (outf, "  base_object: ");
  print_generic_stmt (outf, DR_BASE_OBJECT (dr), 0);
  
  for (i = 0; i < DR_NUM_DIMENSIONS (dr); i++)
    {
      fprintf (outf, "  Access function %d: ", i);
      print_generic_stmt (outf, DR_ACCESS_FN (dr, i), 0);
    }
  fprintf (outf, ")\n");
}