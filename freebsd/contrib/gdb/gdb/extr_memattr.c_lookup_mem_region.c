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
struct mem_region {int enabled_p; scalar_t__ lo; scalar_t__ hi; int /*<<< orphan*/  attrib; struct mem_region* next; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  default_mem_attrib ; 
 struct mem_region* mem_region_chain ; 

struct mem_region *
lookup_mem_region (CORE_ADDR addr)
{
  static struct mem_region region;
  struct mem_region *m;
  CORE_ADDR lo;
  CORE_ADDR hi;

  /* First we initialize LO and HI so that they describe the entire
     memory space.  As we process the memory region chain, they are
     redefined to describe the minimal region containing ADDR.  LO
     and HI are used in the case where no memory region is defined
     that contains ADDR.  If a memory region is disabled, it is
     treated as if it does not exist.  */

  lo = (CORE_ADDR) 0;
  hi = (CORE_ADDR) ~ 0;

  for (m = mem_region_chain; m; m = m->next)
    {
      if (m->enabled_p == 1)
	{
	  if (addr >= m->lo && (addr < m->hi || m->hi == 0))
	    return m;

	  if (addr >= m->hi && lo < m->hi)
	    lo = m->hi;

	  if (addr <= m->lo && hi > m->lo)
	    hi = m->lo;
	}
    }

  /* Because no region was found, we must cons up one based on what
     was learned above.  */
  region.lo = lo;
  region.hi = hi;
  region.attrib = default_mem_attrib;
  return &region;
}