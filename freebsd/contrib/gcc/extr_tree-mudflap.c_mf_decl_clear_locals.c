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
 void* NULL_TREE ; 
 void* mf_cache_mask_decl_l ; 
 void* mf_cache_shift_decl_l ; 

__attribute__((used)) static void
mf_decl_clear_locals (void)
{
  /* Unset local shadows.  */
  mf_cache_shift_decl_l = NULL_TREE;
  mf_cache_mask_decl_l = NULL_TREE;
}