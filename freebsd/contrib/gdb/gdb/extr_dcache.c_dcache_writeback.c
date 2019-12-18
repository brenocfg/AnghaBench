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
struct dcache_block {struct dcache_block* p; } ;
struct TYPE_4__ {struct dcache_block* valid_head; } ;
typedef  TYPE_1__ DCACHE ;

/* Variables and functions */
 int /*<<< orphan*/  dcache_write_line (TYPE_1__*,struct dcache_block*) ; 

__attribute__((used)) static int
dcache_writeback (DCACHE *dcache)
{
  struct dcache_block *db;

  db = dcache->valid_head;

  while (db)
    {
      if (!dcache_write_line (dcache, db))
	return 0;
      db = db->p;
    }
  return 1;
}