#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hash_table; } ;
typedef  TYPE_1__ cpp_reader ;
typedef  int /*<<< orphan*/  cpp_hashnode ;

/* Variables and functions */
 int /*<<< orphan*/ * CPP_HASHNODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HT_ALLOC ; 
 int /*<<< orphan*/  ht_lookup (int /*<<< orphan*/ ,unsigned char const*,unsigned int,int /*<<< orphan*/ ) ; 

cpp_hashnode *
cpp_lookup (cpp_reader *pfile, const unsigned char *str, unsigned int len)
{
  /* ht_lookup cannot return NULL.  */
  return CPP_HASHNODE (ht_lookup (pfile->hash_table, str, len, HT_ALLOC));
}