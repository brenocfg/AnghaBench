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
 scalar_t__ DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  flag_mudflap_threads ; 
 int /*<<< orphan*/  mf_decl_cache_locals () ; 
 int /*<<< orphan*/  mf_decl_clear_locals () ; 
 scalar_t__ mf_marked_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mf_xform_derefs () ; 
 int /*<<< orphan*/  pop_gimplify_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_gimplify_context () ; 

__attribute__((used)) static unsigned int
execute_mudflap_function_ops (void)
{
  /* Don't instrument functions such as the synthetic constructor
     built during mudflap_finish_file.  */
  if (mf_marked_p (current_function_decl) ||
      DECL_ARTIFICIAL (current_function_decl))
    return 0;

  push_gimplify_context ();

  /* In multithreaded mode, don't cache the lookup cache parameters.  */
  if (! flag_mudflap_threads)
    mf_decl_cache_locals ();

  mf_xform_derefs ();

  if (! flag_mudflap_threads)
    mf_decl_clear_locals ();

  pop_gimplify_context (NULL);
  return 0;
}