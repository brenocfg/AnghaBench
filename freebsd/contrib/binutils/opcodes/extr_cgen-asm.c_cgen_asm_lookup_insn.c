#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int (* asm_hash ) (char const*) ;int /*<<< orphan*/ ** asm_hash_table; } ;
typedef  int /*<<< orphan*/  CGEN_INSN_LIST ;
typedef  TYPE_1__* CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  build_asm_hash_table (TYPE_1__*) ; 
 unsigned int stub1 (char const*) ; 

CGEN_INSN_LIST *
cgen_asm_lookup_insn (CGEN_CPU_DESC cd, const char *insn)
{
  unsigned int hash;

  if (cd->asm_hash_table == NULL)
    build_asm_hash_table (cd);

  hash = (* cd->asm_hash) (insn);
  return cd->asm_hash_table[hash];
}