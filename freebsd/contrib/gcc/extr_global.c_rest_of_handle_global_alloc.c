#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  static_pass_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  TV_DUMP ; 
 int /*<<< orphan*/  build_insn_chain (int /*<<< orphan*/ ) ; 
 scalar_t__ dump_enabled_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_file ; 
 int /*<<< orphan*/  dump_global_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_insns () ; 
 int global_alloc () ; 
 scalar_t__ optimize ; 
 TYPE_1__ pass_global_alloc ; 
 int reload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reload_completed ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
rest_of_handle_global_alloc (void)
{
  bool failure;

  /* If optimizing, allocate remaining pseudo-regs.  Do the reload
     pass fixing up any insns that are invalid.  */

  if (optimize)
    failure = global_alloc ();
  else
    {
      build_insn_chain (get_insns ());
      failure = reload (get_insns (), 0);
    }

  if (dump_enabled_p (pass_global_alloc.static_pass_number))
    {
      timevar_push (TV_DUMP);
      dump_global_regs (dump_file);
      timevar_pop (TV_DUMP);
    }

  gcc_assert (reload_completed || failure);
  reload_completed = !failure;
  return 0;
}