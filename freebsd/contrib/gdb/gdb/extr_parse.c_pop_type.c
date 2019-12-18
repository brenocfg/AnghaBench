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
typedef  enum type_pieces { ____Placeholder_type_pieces } type_pieces ;
struct TYPE_2__ {int piece; } ;

/* Variables and functions */
 int tp_end ; 
 TYPE_1__* type_stack ; 
 int type_stack_depth ; 

enum type_pieces
pop_type (void)
{
  if (type_stack_depth)
    return type_stack[--type_stack_depth].piece;
  return tp_end;
}