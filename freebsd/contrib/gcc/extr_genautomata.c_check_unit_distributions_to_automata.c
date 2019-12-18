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
typedef  TYPE_1__* decl_t ;
struct TYPE_7__ {int /*<<< orphan*/  transformed_regexp; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_5__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_3__* DECL_INSN_RESERV (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  annotation_message_reported_p ; 
 int /*<<< orphan*/  check_regexp_units_distribution (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* description ; 
 scalar_t__ dm_insn_reserv ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ progress_flag ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
check_unit_distributions_to_automata (void)
{
  decl_t decl;
  int i;

  if (progress_flag)
    fprintf (stderr, "Check unit distributions to automata...");
  annotation_message_reported_p = FALSE;
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_insn_reserv)
	check_regexp_units_distribution
	  (DECL_INSN_RESERV (decl)->name,
	   DECL_INSN_RESERV (decl)->transformed_regexp);
    }
  if (progress_flag)
    fprintf (stderr, "done\n");
}