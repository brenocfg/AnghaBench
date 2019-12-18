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
struct dataflow {int flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DF_RI_LIFE ; 
 int /*<<< orphan*/  dump_flow_info (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  print_rtl_with_bb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
df_ri_dump (struct dataflow *dflow, FILE *file)
{
  print_rtl_with_bb (file, get_insns ());

  if (dflow->flags & DF_RI_LIFE)
    {
      fprintf (file, "Register info:\n");
      dump_flow_info (file, -1);
    }
}