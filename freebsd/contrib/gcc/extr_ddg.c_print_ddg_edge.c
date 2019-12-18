#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* ddg_edge_ptr ;
struct TYPE_7__ {int type; int latency; int distance; TYPE_1__* dest; TYPE_2__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  insn; } ;
struct TYPE_5__ {int /*<<< orphan*/  insn; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ANTI_DEP 129 
 int INSN_UID (int /*<<< orphan*/ ) ; 
#define  OUTPUT_DEP 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,char,int,int,int) ; 

void
print_ddg_edge (FILE *file, ddg_edge_ptr e)
{
  char dep_c;

  switch (e->type) {
    case OUTPUT_DEP :
      dep_c = 'O';
      break;
    case ANTI_DEP :
      dep_c = 'A';
      break;
    default:
      dep_c = 'T';
  }

  fprintf (file, " [%d -(%c,%d,%d)-> %d] ", INSN_UID (e->src->insn),
	   dep_c, e->latency, e->distance, INSN_UID (e->dest->insn));
}