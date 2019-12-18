#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_11__ {int latency; } ;
struct TYPE_10__ {int default_latency; } ;
struct TYPE_9__ {int max_insn_reserv_cycles; int decls_num; TYPE_1__** decls; } ;
struct TYPE_8__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_6__* DECL_BYPASS (TYPE_1__*) ; 
 TYPE_4__* DECL_INSN_RESERV (TYPE_1__*) ; 
 TYPE_1__* advance_cycle_insn_decl ; 
 TYPE_2__* description ; 
 scalar_t__ dm_bypass ; 
 scalar_t__ dm_insn_reserv ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_max_insn_queue_index_def (void)
{
  int i, max, latency;
  decl_t decl;

  max = description->max_insn_reserv_cycles;
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_insn_reserv && decl != advance_cycle_insn_decl)
	{
	  latency = DECL_INSN_RESERV (decl)->default_latency;
	  if (latency > max)
	    max = latency;
	}
      else if (decl->mode == dm_bypass)
	{
	  latency = DECL_BYPASS (decl)->latency;
	  if (latency > max)
	    max = latency;
	}
    }
  for (i = 0; (1 << i) <= max; i++)
    ;
  gcc_assert (i >= 0);
  fprintf (output_file, "\nconst int max_insn_queue_index = %d;\n\n",
	   (1 << i) - 1);
}