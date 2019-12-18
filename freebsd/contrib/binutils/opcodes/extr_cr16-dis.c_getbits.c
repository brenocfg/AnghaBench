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
typedef  size_t operand_type ;
struct TYPE_2__ {int bit_size; } ;

/* Variables and functions */
 size_t MAX_OPRD ; 
 TYPE_1__* cr16_optab ; 

__attribute__((used)) static int
getbits (operand_type op)
{
  if (op < MAX_OPRD)
    return cr16_optab[op].bit_size;

  return 0;
}