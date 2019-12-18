#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  (* destructor ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* constructor ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; scalar_t__ have_ctors_dtors; } ;

/* Variables and functions */
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_STATIC_CONSTRUCTOR (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_STATIC_DESTRUCTOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_INIT_PRIORITY ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/  tree_rest_of_compilation (int /*<<< orphan*/ ) ; 

void
c_expand_body (tree fndecl)
{

  if (!DECL_INITIAL (fndecl)
      || DECL_INITIAL (fndecl) == error_mark_node)
    return;

  tree_rest_of_compilation (fndecl);

  if (DECL_STATIC_CONSTRUCTOR (fndecl)
      && targetm.have_ctors_dtors)
    targetm.asm_out.constructor (XEXP (DECL_RTL (fndecl), 0),
				 DEFAULT_INIT_PRIORITY);
  if (DECL_STATIC_DESTRUCTOR (fndecl)
      && targetm.have_ctors_dtors)
    targetm.asm_out.destructor (XEXP (DECL_RTL (fndecl), 0),
				DEFAULT_INIT_PRIORITY);
}