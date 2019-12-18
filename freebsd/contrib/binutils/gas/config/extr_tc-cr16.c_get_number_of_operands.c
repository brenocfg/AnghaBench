#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* operands; } ;
struct TYPE_3__ {scalar_t__ op_type; } ;

/* Variables and functions */
 int MAX_OPERANDS ; 
 TYPE_2__* instruction ; 

__attribute__((used)) static int
get_number_of_operands (void)
{
  int i;

  for (i = 0; instruction->operands[i].op_type && i < MAX_OPERANDS; i++)
    ;
  return i;
}