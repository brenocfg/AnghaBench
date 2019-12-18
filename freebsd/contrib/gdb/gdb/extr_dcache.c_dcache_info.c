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
struct dcache_block {int* data; int /*<<< orphan*/ * state; int /*<<< orphan*/  refs; int /*<<< orphan*/  addr; struct dcache_block* p; } ;
struct TYPE_2__ {struct dcache_block* valid_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_SIZE ; 
 int LINE_SIZE ; 
 TYPE_1__* last_cache ; 
 int /*<<< orphan*/  paddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 

__attribute__((used)) static void
dcache_info (char *exp, int tty)
{
  struct dcache_block *p;

  printf_filtered ("Dcache line width %d, depth %d\n",
		   LINE_SIZE, DCACHE_SIZE);

  if (last_cache)
    {
      printf_filtered ("Cache state:\n");

      for (p = last_cache->valid_head; p; p = p->p)
	{
	  int j;
	  printf_filtered ("Line at %s, referenced %d times\n",
			   paddr (p->addr), p->refs);

	  for (j = 0; j < LINE_SIZE; j++)
	    printf_filtered ("%02x", p->data[j] & 0xFF);
	  printf_filtered ("\n");

	  for (j = 0; j < LINE_SIZE; j++)
	    printf_filtered ("%2x", p->state[j]);
	  printf_filtered ("\n");
	}
    }
}