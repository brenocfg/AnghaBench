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
typedef  enum compare_op { ____Placeholder_compare_op } compare_op ;

/* Variables and functions */
#define  COMPARE_OP_EQUAL 133 
#define  COMPARE_OP_GREATER 132 
#define  COMPARE_OP_GREATER_EQUAL 131 
#define  COMPARE_OP_LESS 130 
#define  COMPARE_OP_LESS_EQUAL 129 
#define  COMPARE_OP_NOT_EQUAL 128 

__attribute__((used)) static bool core_info_compare_api_version(int sys_major, int sys_minor, int major, int minor, enum compare_op op)
{
   switch (op)
   {
      case COMPARE_OP_EQUAL:
         if (sys_major == major && sys_minor == minor)
            return true;
         break;
      case COMPARE_OP_NOT_EQUAL:
         if (!(sys_major == major && sys_minor == minor))
            return true;
         break;
      case COMPARE_OP_LESS:
         if (sys_major < major || (sys_major == major && sys_minor < minor))
            return true;
         break;
      case COMPARE_OP_LESS_EQUAL:
         if (sys_major < major || (sys_major == major && sys_minor <= minor))
            return true;
         break;
      case COMPARE_OP_GREATER:
         if (sys_major > major || (sys_major == major && sys_minor > minor))
            return true;
         break;
      case COMPARE_OP_GREATER_EQUAL:
         if (sys_major > major || (sys_major == major && sys_minor >= minor))
            return true;
         break;
      default:
         break;
   }

   return false;
}