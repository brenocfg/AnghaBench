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

/* Variables and functions */
#define  BUILT_IN_MEMCPY 141 
#define  BUILT_IN_MEMCPY_CHK 140 
#define  BUILT_IN_MEMMOVE 139 
#define  BUILT_IN_MEMMOVE_CHK 138 
#define  BUILT_IN_MEMSET 137 
#define  BUILT_IN_MEMSET_CHK 136 
 scalar_t__ BUILT_IN_NORMAL ; 
#define  BUILT_IN_STRCAT 135 
#define  BUILT_IN_STRCAT_CHK 134 
#define  BUILT_IN_STRCPY 133 
#define  BUILT_IN_STRCPY_CHK 132 
#define  BUILT_IN_STRNCAT 131 
#define  BUILT_IN_STRNCAT_CHK 130 
#define  BUILT_IN_STRNCPY 129 
#define  BUILT_IN_STRNCPY_CHK 128 
 scalar_t__ DECL_BUILT_IN_CLASS (scalar_t__) ; 
 int DECL_FUNCTION_CODE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ get_callee_fndecl (scalar_t__) ; 

__attribute__((used)) static tree
pass_through_call (tree call)
{
  tree callee = get_callee_fndecl (call);
  tree arglist = TREE_OPERAND (call, 1);

  if (callee
      && DECL_BUILT_IN_CLASS (callee) == BUILT_IN_NORMAL)
    switch (DECL_FUNCTION_CODE (callee))
      {
      case BUILT_IN_MEMCPY:
      case BUILT_IN_MEMMOVE:
      case BUILT_IN_MEMSET:
      case BUILT_IN_STRCPY:
      case BUILT_IN_STRNCPY:
      case BUILT_IN_STRCAT:
      case BUILT_IN_STRNCAT:
      case BUILT_IN_MEMCPY_CHK:
      case BUILT_IN_MEMMOVE_CHK:
      case BUILT_IN_MEMSET_CHK:
      case BUILT_IN_STRCPY_CHK:
      case BUILT_IN_STRNCPY_CHK:
      case BUILT_IN_STRCAT_CHK:
      case BUILT_IN_STRNCAT_CHK:
	if (arglist)
	  return TREE_VALUE (arglist);
	break;
      default:
	break;
      }

  return NULL_TREE;
}