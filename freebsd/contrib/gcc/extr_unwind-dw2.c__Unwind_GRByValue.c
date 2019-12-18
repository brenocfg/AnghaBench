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
struct _Unwind_Context {int* by_value; } ;

/* Variables and functions */
 int DWARF_REG_TO_UNWIND_COLUMN (int) ; 

__attribute__((used)) static inline int
_Unwind_GRByValue (struct _Unwind_Context *context, int index)
{
  index = DWARF_REG_TO_UNWIND_COLUMN (index);
  return context->by_value[index];
}