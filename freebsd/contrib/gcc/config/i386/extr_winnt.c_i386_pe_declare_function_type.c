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
 scalar_t__ C_EXT ; 
 scalar_t__ C_STAT ; 
 scalar_t__ DT_FCN ; 
 int N_BTSHFT ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
i386_pe_declare_function_type (FILE *file, const char *name, int public)
{
  fprintf (file, "\t.def\t");
  assemble_name (file, name);
  fprintf (file, ";\t.scl\t%d;\t.type\t%d;\t.endef\n",
	   public ? (int) C_EXT : (int) C_STAT,
	   (int) DT_FCN << N_BTSHFT);
}