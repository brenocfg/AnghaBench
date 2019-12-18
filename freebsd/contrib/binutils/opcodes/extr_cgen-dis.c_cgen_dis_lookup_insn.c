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
struct TYPE_4__ {unsigned int (* dis_hash ) (char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ ** dis_hash_table; } ;
typedef  int /*<<< orphan*/  CGEN_INSN_LIST ;
typedef  int /*<<< orphan*/  CGEN_INSN_INT ;
typedef  TYPE_1__* CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  build_dis_hash_table (TYPE_1__*) ; 
 unsigned int stub1 (char const*,int /*<<< orphan*/ ) ; 

CGEN_INSN_LIST *
cgen_dis_lookup_insn (CGEN_CPU_DESC cd, const char * buf, CGEN_INSN_INT value)
{
  unsigned int hash;

  if (cd->dis_hash_table == NULL)
    build_dis_hash_table (cd);

  hash = (* cd->dis_hash) (buf, value);

  return cd->dis_hash_table[hash];
}