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
 unsigned int CLEANUP_CFGLAYOUT ; 
 int /*<<< orphan*/  cfg_layout_rtl_register_cfg_hooks () ; 
 int /*<<< orphan*/  cleanup_cfg (unsigned int) ; 
 int /*<<< orphan*/  initialize_original_copy_tables () ; 
 int /*<<< orphan*/  record_effective_endpoints () ; 

void
cfg_layout_initialize (unsigned int flags)
{
  initialize_original_copy_tables ();

  cfg_layout_rtl_register_cfg_hooks ();

  record_effective_endpoints ();

  cleanup_cfg (CLEANUP_CFGLAYOUT | flags);
}