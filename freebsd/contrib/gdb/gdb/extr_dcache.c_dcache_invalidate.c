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
struct dcache_block {struct dcache_block* p; } ;
struct TYPE_3__ {struct dcache_block* free_tail; struct dcache_block* free_head; struct dcache_block* the_cache; scalar_t__ valid_tail; scalar_t__ valid_head; } ;
typedef  TYPE_1__ DCACHE ;

/* Variables and functions */
 int DCACHE_SIZE ; 

void
dcache_invalidate (DCACHE *dcache)
{
  int i;
  dcache->valid_head = 0;
  dcache->valid_tail = 0;

  dcache->free_head = 0;
  dcache->free_tail = 0;

  for (i = 0; i < DCACHE_SIZE; i++)
    {
      struct dcache_block *db = dcache->the_cache + i;

      if (!dcache->free_head)
	dcache->free_head = db;
      else
	dcache->free_tail->p = db;
      dcache->free_tail = db;
      db->p = 0;
    }

  return;
}