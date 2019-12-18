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
struct ia64_opcode {int dummy; } ;

/* Variables and functions */
 struct ia64_opcode* ia64_find_next_opcode (struct ia64_opcode*) ; 
 int /*<<< orphan*/  ia64_free_opcode (struct ia64_opcode*) ; 

__attribute__((used)) static struct ia64_opcode *
get_next_opcode (struct ia64_opcode *idesc)
{
  struct ia64_opcode *next = ia64_find_next_opcode (idesc);
  ia64_free_opcode (idesc);
  return next;
}