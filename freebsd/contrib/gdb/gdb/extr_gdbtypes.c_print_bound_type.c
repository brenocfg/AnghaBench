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
#define  BOUND_BY_REF_IN_REG 133 
#define  BOUND_BY_REF_ON_STACK 132 
#define  BOUND_BY_VALUE_IN_REG 131 
#define  BOUND_BY_VALUE_ON_STACK 130 
#define  BOUND_CANNOT_BE_DETERMINED 129 
#define  BOUND_SIMPLE 128 
 int /*<<< orphan*/  printf_filtered (char*) ; 

__attribute__((used)) static void
print_bound_type (int bt)
{
  switch (bt)
    {
    case BOUND_CANNOT_BE_DETERMINED:
      printf_filtered ("(BOUND_CANNOT_BE_DETERMINED)");
      break;
    case BOUND_BY_REF_ON_STACK:
      printf_filtered ("(BOUND_BY_REF_ON_STACK)");
      break;
    case BOUND_BY_VALUE_ON_STACK:
      printf_filtered ("(BOUND_BY_VALUE_ON_STACK)");
      break;
    case BOUND_BY_REF_IN_REG:
      printf_filtered ("(BOUND_BY_REF_IN_REG)");
      break;
    case BOUND_BY_VALUE_IN_REG:
      printf_filtered ("(BOUND_BY_VALUE_IN_REG)");
      break;
    case BOUND_SIMPLE:
      printf_filtered ("(BOUND_SIMPLE)");
      break;
    default:
      printf_filtered ("(unknown bound type)");
      break;
    }
}