#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ *** page_table ;
typedef  int /*<<< orphan*/  page_entry ;
struct TYPE_4__ {int /*<<< orphan*/ *** lookup; } ;
struct TYPE_3__ {size_t high_bits; int /*<<< orphan*/ *** table; int /*<<< orphan*/ *** next; } ;

/* Variables and functions */
 TYPE_2__ G ; 
 size_t LOOKUP_L1 (void const*) ; 
 size_t LOOKUP_L2 (void const*) ; 

__attribute__((used)) static inline int
ggc_allocated_p (const void *p)
{
  page_entry ***base;
  size_t L1, L2;

#if HOST_BITS_PER_PTR <= 32
  base = &G.lookup[0];
#else
  page_table table = G.lookup;
  size_t high_bits = (size_t) p & ~ (size_t) 0xffffffff;
  while (1)
    {
      if (table == NULL)
	return 0;
      if (table->high_bits == high_bits)
	break;
      table = table->next;
    }
  base = &table->table[0];
#endif

  /* Extract the level 1 and 2 indices.  */
  L1 = LOOKUP_L1 (p);
  L2 = LOOKUP_L2 (p);

  return base[L1] && base[L1][L2];
}