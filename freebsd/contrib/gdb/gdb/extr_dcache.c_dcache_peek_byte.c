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
struct dcache_block {scalar_t__* state; char* data; } ;
typedef  int /*<<< orphan*/  DCACHE ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ENTRY_BAD ; 
 size_t XFORM (int /*<<< orphan*/ ) ; 
 struct dcache_block* dcache_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dcache_block* dcache_hit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcache_read_line (int /*<<< orphan*/ *,struct dcache_block*) ; 

__attribute__((used)) static int
dcache_peek_byte (DCACHE *dcache, CORE_ADDR addr, char *ptr)
{
  struct dcache_block *db = dcache_hit (dcache, addr);

  if (!db)
    {
      db = dcache_alloc (dcache, addr);
      if (!db)
	return 0;
    }
  
  if (db->state[XFORM (addr)] == ENTRY_BAD)
    {
      if (!dcache_read_line(dcache, db))
         return 0;
    }

  *ptr = db->data[XFORM (addr)];
  return 1;
}