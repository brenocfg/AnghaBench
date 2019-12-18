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
typedef  scalar_t__ pointer ;

/* Variables and functions */
 int /*<<< orphan*/  emit_movimm (scalar_t__,unsigned int) ; 
 scalar_t__ out ; 

void emit_load_return_address(unsigned int rt)
{
  // (assumes this instruction will be followed by a 5-byte jmp instruction)
  emit_movimm((pointer)out+10,rt);
}