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
struct dcache_block {scalar_t__ addr; struct dcache_block* p; int /*<<< orphan*/  refs; } ;
struct TYPE_3__ {struct dcache_block* valid_head; } ;
typedef  TYPE_1__ DCACHE ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ MASK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dcache_block *
dcache_hit (DCACHE *dcache, CORE_ADDR addr)
{
  struct dcache_block *db;

  /* Search all cache blocks for one that is at this address.  */
  db = dcache->valid_head;

  while (db)
    {
      if (MASK (addr) == db->addr)
	{
	  db->refs++;
	  return db;
	}
      db = db->p;
    }

  return NULL;
}