#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  assembler_name; } ;
struct TYPE_6__ {TYPE_1__ decl_with_vis; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_decl_assembler_name ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME_SET_P (int /*<<< orphan*/ ) ; 
 TYPE_3__* DECL_WITH_VIS_CHECK (int /*<<< orphan*/ ) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

tree
decl_assembler_name (tree decl)
{
  if (!DECL_ASSEMBLER_NAME_SET_P (decl))
    lang_hooks.set_decl_assembler_name (decl);
  return DECL_WITH_VIS_CHECK (decl)->decl_with_vis.assembler_name;
}