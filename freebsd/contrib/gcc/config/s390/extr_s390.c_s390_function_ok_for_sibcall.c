#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {int /*<<< orphan*/  (* binds_local_p ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TARGET_64BIT ; 
 scalar_t__ TARGET_TPF_PROFILING ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ flag_pic ; 
 scalar_t__ s390_call_saved_register_used (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static bool
s390_function_ok_for_sibcall (tree decl, tree exp)
{
  /* The TPF epilogue uses register 1.  */
  if (TARGET_TPF_PROFILING)
    return false;

  /* The 31 bit PLT code uses register 12 (GOT pointer - caller saved)
     which would have to be restored before the sibcall.  */
  if (!TARGET_64BIT && flag_pic && decl && !targetm.binds_local_p (decl))
    return false;

  /* Register 6 on s390 is available as an argument register but unfortunately
     "caller saved". This makes functions needing this register for arguments
     not suitable for sibcalls.  */
  if (TREE_OPERAND (exp, 1)
      && s390_call_saved_register_used (TREE_OPERAND (exp, 1)))
      return false;

  return true;
}