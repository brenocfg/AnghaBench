#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* ddg_ptr ;
typedef  TYPE_4__* ddg_edge_ptr ;
struct TYPE_9__ {int distance; int latency; TYPE_2__* dest; struct TYPE_9__* next_out; } ;
struct TYPE_8__ {int num_nodes; TYPE_1__* nodes; } ;
struct TYPE_7__ {int cuid; int /*<<< orphan*/  insn; } ;
struct TYPE_6__ {TYPE_4__* out; int /*<<< orphan*/  insn; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  print_rtl_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
vcg_print_ddg (FILE *file, ddg_ptr g)
{
  int src_cuid;

  fprintf (file, "graph: {\n");
  for (src_cuid = 0; src_cuid < g->num_nodes; src_cuid++)
    {
      ddg_edge_ptr e;
      int src_uid = INSN_UID (g->nodes[src_cuid].insn);

      fprintf (file, "node: {title: \"%d_%d\" info1: \"", src_cuid, src_uid);
      print_rtl_single (file, g->nodes[src_cuid].insn);
      fprintf (file, "\"}\n");
      for (e = g->nodes[src_cuid].out; e; e = e->next_out)
	{
	  int dst_uid = INSN_UID (e->dest->insn);
	  int dst_cuid = e->dest->cuid;

	  /* Give the backarcs a different color.  */
	  if (e->distance > 0)
	    fprintf (file, "backedge: {color: red ");
	  else
	    fprintf (file, "edge: { ");

	  fprintf (file, "sourcename: \"%d_%d\" ", src_cuid, src_uid);
	  fprintf (file, "targetname: \"%d_%d\" ", dst_cuid, dst_uid);
	  fprintf (file, "label: \"%d_%d\"}\n", e->latency, e->distance);
	}
    }
  fprintf (file, "}\n");
}