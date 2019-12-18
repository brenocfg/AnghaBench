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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_ARG_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  DECL_INCOMING_RTL (scalar_t__) ; 
 int DECL_MODE (scalar_t__) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int promote_mode (int /*<<< orphan*/ ,int,int*,int) ; 

rtx
promoted_input_arg (unsigned int regno, enum machine_mode *pmode, int *punsignedp)
{
  tree arg;

  for (arg = DECL_ARGUMENTS (current_function_decl); arg;
       arg = TREE_CHAIN (arg))
    if (REG_P (DECL_INCOMING_RTL (arg))
	&& REGNO (DECL_INCOMING_RTL (arg)) == regno
	&& TYPE_MODE (DECL_ARG_TYPE (arg)) == TYPE_MODE (TREE_TYPE (arg)))
      {
	enum machine_mode mode = TYPE_MODE (TREE_TYPE (arg));
	int unsignedp = TYPE_UNSIGNED (TREE_TYPE (arg));

	mode = promote_mode (TREE_TYPE (arg), mode, &unsignedp, 1);
	if (mode == GET_MODE (DECL_INCOMING_RTL (arg))
	    && mode != DECL_MODE (arg))
	  {
	    *pmode = DECL_MODE (arg);
	    *punsignedp = unsignedp;
	    return DECL_INCOMING_RTL (arg);
	  }
      }

  return 0;
}