#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * symbol; struct TYPE_6__* next; int /*<<< orphan*/  sub_section; int /*<<< orphan*/  section; scalar_t__ next_free_entry; } ;
typedef  TYPE_1__ literal_pool ;

/* Variables and functions */
 int /*<<< orphan*/  FAKE_LABEL_NAME ; 
 TYPE_1__* find_literal_pool () ; 
 TYPE_1__* list_of_pools ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 int /*<<< orphan*/ * symbol_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  undefined_section ; 
 TYPE_1__* xmalloc (int) ; 
 int /*<<< orphan*/  zero_address_frag ; 

__attribute__((used)) static literal_pool *
find_or_make_literal_pool (void)
{
  /* Next literal pool ID number.  */
  static unsigned int latest_pool_num = 1;
  literal_pool *      pool;

  pool = find_literal_pool ();

  if (pool == NULL)
    {
      /* Create a new pool.  */
      pool = xmalloc (sizeof (* pool));
      if (! pool)
	return NULL;

      pool->next_free_entry = 0;
      pool->section	    = now_seg;
      pool->sub_section	    = now_subseg;
      pool->next	    = list_of_pools;
      pool->symbol	    = NULL;

      /* Add it to the list.  */
      list_of_pools = pool;
    }

  /* New pools, and emptied pools, will have a NULL symbol.  */
  if (pool->symbol == NULL)
    {
      pool->symbol = symbol_create (FAKE_LABEL_NAME, undefined_section,
				    (valueT) 0, &zero_address_frag);
      pool->id = latest_pool_num ++;
    }

  /* Done.  */
  return pool;
}