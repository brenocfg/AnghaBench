#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* decl_t ;
struct TYPE_8__ {int /*<<< orphan*/  regexp; int /*<<< orphan*/  transformed_regexp; } ;
struct TYPE_7__ {int decls_num; TYPE_1__** decls; } ;
struct TYPE_6__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_4__* DECL_INSN_RESERV (TYPE_1__*) ; 
 int /*<<< orphan*/  add_advance_cycle_insn_decl () ; 
 TYPE_1__* advance_cycle_insn_decl ; 
 int /*<<< orphan*/  copy_insn_regexp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_ticker () ; 
 TYPE_2__* description ; 
 scalar_t__ dm_insn_reserv ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ progress_flag ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ticker_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transform_regexp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transform_time ; 

__attribute__((used)) static void
transform_insn_regexps (void)
{
  decl_t decl;
  int i;

  transform_time = create_ticker ();
  add_advance_cycle_insn_decl ();
  if (progress_flag)
    fprintf (stderr, "Reservation transformation...");
  for (i = 0; i < description->decls_num; i++)
    {
      decl = description->decls [i];
      if (decl->mode == dm_insn_reserv && decl != advance_cycle_insn_decl)
	DECL_INSN_RESERV (decl)->transformed_regexp
	  = transform_regexp (copy_insn_regexp
			      (DECL_INSN_RESERV (decl)->regexp));
    }
  if (progress_flag)
    fprintf (stderr, "done\n");
  ticker_off (&transform_time);
}