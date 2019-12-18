#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  hash_table; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_2__ cpp_hashnode ;

/* Variables and functions */
 TYPE_2__* CPP_HASHNODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_NO_INSERT ; 
 scalar_t__ NT_MACRO ; 
 int /*<<< orphan*/  ht_lookup (int /*<<< orphan*/ ,unsigned char const*,int,int /*<<< orphan*/ ) ; 

int
cpp_defined (cpp_reader *pfile, const unsigned char *str, int len)
{
  cpp_hashnode *node;

  node = CPP_HASHNODE (ht_lookup (pfile->hash_table, str, len, HT_NO_INSERT));

  /* If it's of type NT_MACRO, it cannot be poisoned.  */
  return node && node->type == NT_MACRO;
}