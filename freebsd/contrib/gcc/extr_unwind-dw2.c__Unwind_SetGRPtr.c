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
struct _Unwind_Context {void** reg; scalar_t__* by_value; } ;

/* Variables and functions */
 int DWARF_REG_TO_UNWIND_COLUMN (int) ; 
 scalar_t__ _Unwind_IsExtendedContext (struct _Unwind_Context*) ; 

__attribute__((used)) static inline void
_Unwind_SetGRPtr (struct _Unwind_Context *context, int index, void *p)
{
  index = DWARF_REG_TO_UNWIND_COLUMN (index);
  if (_Unwind_IsExtendedContext (context))
    context->by_value[index] = 0;
  context->reg[index] = p;
}