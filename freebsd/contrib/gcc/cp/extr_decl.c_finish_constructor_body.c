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
struct TYPE_3__ {scalar_t__ (* cdtor_returns_this ) () ;} ;
struct TYPE_4__ {TYPE_1__ cxx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_EXPR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 int /*<<< orphan*/  RETURN_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdtor_label ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ stub1 () ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void
finish_constructor_body (void)
{
  tree val;
  tree exprstmt;

  if (targetm.cxx.cdtor_returns_this ())
    {
      /* Any return from a constructor will end up here.  */
      add_stmt (build_stmt (LABEL_EXPR, cdtor_label));

      val = DECL_ARGUMENTS (current_function_decl);
      val = build2 (MODIFY_EXPR, TREE_TYPE (val),
		    DECL_RESULT (current_function_decl), val);
      /* Return the address of the object.  */
      exprstmt = build_stmt (RETURN_EXPR, val);
      add_stmt (exprstmt);
    }
}