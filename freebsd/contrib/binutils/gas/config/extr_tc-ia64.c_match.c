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
typedef  enum ia64_unit { ____Placeholder_ia64_unit } ia64_unit ;
struct TYPE_2__ {int* exec_unit; } ;

/* Variables and functions */
#define  IA64_TYPE_A 134 
#define  IA64_TYPE_B 133 
#define  IA64_TYPE_DYN 132 
#define  IA64_TYPE_F 131 
#define  IA64_TYPE_I 130 
#define  IA64_TYPE_M 129 
#define  IA64_TYPE_X 128 
 int IA64_UNIT_B ; 
 int IA64_UNIT_F ; 
 int IA64_UNIT_I ; 
 int IA64_UNIT_L ; 
 int IA64_UNIT_M ; 
 TYPE_1__* ia64_templ_desc ; 

__attribute__((used)) static int
match (int templ, int type, int slot)
{
  enum ia64_unit unit;
  int result;

  unit = ia64_templ_desc[templ].exec_unit[slot];
  switch (type)
    {
    case IA64_TYPE_DYN: result = 1; break; /* for nop and break */
    case IA64_TYPE_A:
      result = (unit == IA64_UNIT_I || unit == IA64_UNIT_M);
      break;
    case IA64_TYPE_X:	result = (unit == IA64_UNIT_L); break;
    case IA64_TYPE_I:	result = (unit == IA64_UNIT_I); break;
    case IA64_TYPE_M:	result = (unit == IA64_UNIT_M); break;
    case IA64_TYPE_B:	result = (unit == IA64_UNIT_B); break;
    case IA64_TYPE_F:	result = (unit == IA64_UNIT_F); break;
    default:		result = 0; break;
    }
  return result;
}