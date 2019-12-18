#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* alloc_pool_list ;
typedef  TYPE_2__* alloc_pool ;
struct TYPE_9__ {scalar_t__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {scalar_t__ id; scalar_t__ elts_free; scalar_t__ elts_allocated; TYPE_1__* free_list; scalar_t__ elt_size; } ;
struct TYPE_6__ {struct TYPE_6__* next; } ;

/* Variables and functions */
 TYPE_5__* ALLOCATION_OBJECT_PTR_FROM_USER_PTR (void*) ; 
 int /*<<< orphan*/  allocation_object ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  memset (void*,int,scalar_t__) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ u ; 

void
pool_free (alloc_pool pool, void *ptr)
{
  alloc_pool_list header;

  gcc_assert (ptr);

#ifdef ENABLE_CHECKING
  memset (ptr, 0xaf, pool->elt_size - offsetof (allocation_object, u.data));

  /* Check whether the PTR was allocated from POOL.  */
  gcc_assert (pool->id == ALLOCATION_OBJECT_PTR_FROM_USER_PTR (ptr)->id);

  /* Mark the element to be free.  */
  ALLOCATION_OBJECT_PTR_FROM_USER_PTR (ptr)->id = 0;
#else
  /* Check if we free more than we allocated, which is Bad (TM).  */
  gcc_assert (pool->elts_free < pool->elts_allocated);
#endif

  header = (alloc_pool_list) ptr;
  header->next = pool->free_list;
  pool->free_list = header;
  pool->elts_free++;
}