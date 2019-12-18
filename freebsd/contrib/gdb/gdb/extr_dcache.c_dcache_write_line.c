#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  cache; } ;
struct mem_region {scalar_t__ hi; TYPE_1__ attrib; } ;
struct dcache_block {scalar_t__ addr; char* data; scalar_t__* state; scalar_t__ anydirty; } ;
typedef  int /*<<< orphan*/  DCACHE ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ENTRY_DIRTY ; 
 int /*<<< orphan*/  ENTRY_OK ; 
 int LINE_SIZE ; 
 scalar_t__ MEM_RO ; 
 size_t XFORM (scalar_t__) ; 
 int do_xfer_memory (scalar_t__,char*,int,int,TYPE_1__*) ; 
 struct mem_region* lookup_mem_region (scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dcache_write_line (DCACHE *dcache, struct dcache_block *db)
{
  CORE_ADDR memaddr;
  char *myaddr;
  int len;
  int res;
  int reg_len;
  struct mem_region *region;

  if (!db->anydirty)
    return 1;

  len = LINE_SIZE;
  memaddr = db->addr;
  myaddr  = db->data;

  while (len > 0)
    {
      int s;
      int e;
      int dirty_len;
      
      region = lookup_mem_region(memaddr);
      if (memaddr + len < region->hi)
	reg_len = len;
      else
	reg_len = region->hi - memaddr;

      if (!region->attrib.cache || region->attrib.mode == MEM_RO)
	{
	  memaddr += reg_len;
	  myaddr  += reg_len;
	  len     -= reg_len;
	  continue;
	}

      while (reg_len > 0)
	{
	  s = XFORM(memaddr);
	  while (reg_len > 0) {
	    if (db->state[s] == ENTRY_DIRTY)
	      break;
	    s++;
	    reg_len--;

	    memaddr++;
	    myaddr++;
	    len--;
	  }

	  e = s;
	  while (reg_len > 0) {
	    if (db->state[e] != ENTRY_DIRTY)
	      break;
	    e++;
	    reg_len--;
	  }

	  dirty_len = e - s;
	  while (dirty_len > 0)
	    {
	      res = do_xfer_memory(memaddr, myaddr, dirty_len, 1,
				   &region->attrib);
	      if (res <= 0)
		return 0;

	      memset (&db->state[XFORM(memaddr)], ENTRY_OK, res);
	      memaddr   += res;
	      myaddr    += res;
	      len       -= res;
	      dirty_len -= res;
	    }
	}
    }

  db->anydirty = 0;
  return 1;
}