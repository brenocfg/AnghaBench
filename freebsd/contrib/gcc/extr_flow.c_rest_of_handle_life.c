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

/* Variables and functions */
 int CLEANUP_EXPENSIVE ; 
 int CLEANUP_LOG_LINKS ; 
 int CLEANUP_THREADING ; 
 int CLEANUP_UPDATE_LIFE ; 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int PROP_DEATH_NOTES ; 
 int /*<<< orphan*/  PROP_FINAL ; 
 int PROP_LOG_LINKS ; 
 int PROP_REG_INFO ; 
 int /*<<< orphan*/  UPDATE_LIFE_GLOBAL_RM_NOTES ; 
 int /*<<< orphan*/  allocate_reg_life_data () ; 
 int /*<<< orphan*/  cleanup_cfg (int) ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ extra_warnings ; 
 scalar_t__ flag_thread_jumps ; 
 scalar_t__ initialize_uninitialized_subregs () ; 
 int /*<<< orphan*/  life_analysis (int /*<<< orphan*/ ) ; 
 int no_new_pseudos ; 
 scalar_t__ optimize ; 
 int /*<<< orphan*/  regclass_init () ; 
 int /*<<< orphan*/  setjmp_args_warning () ; 
 int /*<<< orphan*/  setjmp_vars_warning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_life_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
rest_of_handle_life (void)
{
  regclass_init ();

  life_analysis (PROP_FINAL);
  if (optimize)
    cleanup_cfg (CLEANUP_EXPENSIVE | CLEANUP_UPDATE_LIFE | CLEANUP_LOG_LINKS
                 | (flag_thread_jumps ? CLEANUP_THREADING : 0));

  if (extra_warnings)
    {
      setjmp_vars_warning (DECL_INITIAL (current_function_decl));
      setjmp_args_warning ();
    }

  if (optimize)
    {
      if (initialize_uninitialized_subregs ())
        {
          /* Insns were inserted, and possibly pseudos created, so
             things might look a bit different.  */
          allocate_reg_life_data ();
          update_life_info (NULL, UPDATE_LIFE_GLOBAL_RM_NOTES,
                            PROP_LOG_LINKS | PROP_REG_INFO | PROP_DEATH_NOTES);
        }
    }

  no_new_pseudos = 1;
  return 0;
}