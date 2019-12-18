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
struct arc_opcode {int dummy; } ;

/* Variables and functions */
 size_t ARC_HASH_OPCODE (char const*) ; 
 struct arc_opcode const** opcode_map ; 

const struct arc_opcode *
arc_opcode_lookup_asm (const char *insn)
{
  return opcode_map[ARC_HASH_OPCODE (insn)];
}