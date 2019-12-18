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
#define  RC_DUPLICATED_CANCEL 145 
#define  RC_DUPLICATED_PROGRESS 144 
#define  RC_DUPLICATED_START 143 
#define  RC_DUPLICATED_SUBMIT 142 
#define  RC_DUPLICATED_VALUE 141 
#define  RC_INVALID_CONDITION_TYPE 140 
#define  RC_INVALID_CONST_OPERAND 139 
#define  RC_INVALID_FP_OPERAND 138 
#define  RC_INVALID_LBOARD_FIELD 137 
#define  RC_INVALID_LUA_OPERAND 136 
#define  RC_INVALID_MEMORY_OPERAND 135 
#define  RC_INVALID_OPERATOR 134 
#define  RC_INVALID_REQUIRED_HITS 133 
#define  RC_MISSING_CANCEL 132 
#define  RC_MISSING_START 131 
#define  RC_MISSING_SUBMIT 130 
#define  RC_MISSING_VALUE 129 
#define  RC_OK 128 

__attribute__((used)) static const char* rcheevos_rc_error(int ret)
{
   switch (ret)
   {
      case RC_OK: return "Ok";
      case RC_INVALID_LUA_OPERAND: return "Invalid Lua operand";
      case RC_INVALID_MEMORY_OPERAND: return "Invalid memory operand";
      case RC_INVALID_CONST_OPERAND: return "Invalid constant operand";
      case RC_INVALID_FP_OPERAND: return "Invalid floating-point operand";
      case RC_INVALID_CONDITION_TYPE: return "Invalid condition type";
      case RC_INVALID_OPERATOR: return "Invalid operator";
      case RC_INVALID_REQUIRED_HITS: return "Invalid required hits";
      case RC_DUPLICATED_START: return "Duplicated start condition";
      case RC_DUPLICATED_CANCEL: return "Duplicated cancel condition";
      case RC_DUPLICATED_SUBMIT: return "Duplicated submit condition";
      case RC_DUPLICATED_VALUE: return "Duplicated value expression";
      case RC_DUPLICATED_PROGRESS: return "Duplicated progress expression";
      case RC_MISSING_START: return "Missing start condition";
      case RC_MISSING_CANCEL: return "Missing cancel condition";
      case RC_MISSING_SUBMIT: return "Missing submit condition";
      case RC_MISSING_VALUE: return "Missing value expression";
      case RC_INVALID_LBOARD_FIELD: return "Invalid field in leaderboard";
      default: return "Unknown error";
   }
}