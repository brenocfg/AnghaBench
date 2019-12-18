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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  splay_tree_value ;

/* Variables and functions */
 int DECL_UID (scalar_t__) ; 
 int /*<<< orphan*/  all_module_statics ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reference_vars_to_consider ; 
 int /*<<< orphan*/  splay_tree_insert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void 
add_static_var (tree var) 
{
  int uid = DECL_UID (var);
  if (!bitmap_bit_p (all_module_statics, uid))
    {
      splay_tree_insert (reference_vars_to_consider,
			 uid, (splay_tree_value)var);
      bitmap_set_bit (all_module_statics, uid);
    }
}