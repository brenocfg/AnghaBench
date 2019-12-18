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
struct mem_attrib {int dummy; } ;
struct mem_region {scalar_t__ lo; scalar_t__ hi; int enabled_p; struct mem_region* next; struct mem_attrib attrib; scalar_t__ number; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ mem_number ; 
 struct mem_region* mem_region_chain ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 struct mem_region* xmalloc (int) ; 

__attribute__((used)) static struct mem_region *
create_mem_region (CORE_ADDR lo, CORE_ADDR hi,
		   const struct mem_attrib *attrib)
{
  struct mem_region *n, *new;

  /* lo == hi is a useless empty region */
  if (lo >= hi && hi != 0)
    {
      printf_unfiltered ("invalid memory region: low >= high\n");
      return NULL;
    }

  n = mem_region_chain;
  while (n)
    {
      /* overlapping node */
      if ((lo >= n->lo && (lo < n->hi || n->hi == 0)) 
	  || (hi > n->lo && (hi <= n->hi || n->hi == 0))
	  || (lo <= n->lo && (hi >= n->hi || hi == 0)))
	{
	  printf_unfiltered ("overlapping memory region\n");
	  return NULL;
	}
      n = n->next;
    }

  new = xmalloc (sizeof (struct mem_region));
  new->lo = lo;
  new->hi = hi;
  new->number = ++mem_number;
  new->enabled_p = 1;
  new->attrib = *attrib;

  /* link in new node */
  new->next = mem_region_chain;
  mem_region_chain = new;

  return new;
}