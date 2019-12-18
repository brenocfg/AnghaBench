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
struct sparc_opcode_arch {scalar_t__ name; } ;
typedef  enum sparc_opcode_arch_val { ____Placeholder_sparc_opcode_arch_val } sparc_opcode_arch_val ;

/* Variables and functions */
 int SPARC_OPCODE_ARCH_BAD ; 
 struct sparc_opcode_arch const* sparc_opcode_archs ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 

enum sparc_opcode_arch_val
sparc_opcode_lookup_arch (const char *name)
{
  const struct sparc_opcode_arch *p;

  for (p = &sparc_opcode_archs[0]; p->name; ++p)
    if (strcmp (name, p->name) == 0)
      return (enum sparc_opcode_arch_val) (p - &sparc_opcode_archs[0]);

  return SPARC_OPCODE_ARCH_BAD;
}