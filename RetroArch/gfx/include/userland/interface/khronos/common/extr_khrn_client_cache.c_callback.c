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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {void* prev; void* next; } ;
struct TYPE_4__ {TYPE_1__ link; } ;
typedef  int /*<<< orphan*/  KHRN_POINTER_MAP_T ;
typedef  void CACHE_LINK_T ;
typedef  TYPE_2__ CACHE_ENTRY_T ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_pointer_map_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ relocate (void*,void*) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void callback(KHRN_POINTER_MAP_T *map, uint32_t key, void *value, void *user)
{
   CACHE_ENTRY_T *entry = (CACHE_ENTRY_T *)value;

   entry->link.prev = (CACHE_LINK_T *)relocate(entry->link.prev, user);
   entry->link.next = (CACHE_LINK_T *)relocate(entry->link.next, user);

   // Coverity has rightly pointed out that the allocations done in the next codeline can fail
   // verify will only assert the code in debug mode. Use in release mode stays the same as before...
   verify(khrn_pointer_map_insert(map, key, relocate(value, user)));
}