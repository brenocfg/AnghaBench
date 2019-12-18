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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  build_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tinfo_decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_used (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_info_ptr_type ; 

__attribute__((used)) static tree
get_tinfo_ptr (tree type)
{
  tree decl = get_tinfo_decl (type);

  mark_used (decl);
  return build_nop (type_info_ptr_type,
		    build_address (decl));
}