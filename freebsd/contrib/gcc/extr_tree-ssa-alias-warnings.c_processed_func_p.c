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
typedef  void* tree ;
typedef  int /*<<< orphan*/ * htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  gcc_assert (void**) ; 
 int /*<<< orphan*/ * htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_eq_pointer ; 
 void** htab_find_slot (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer ; 

__attribute__((used)) static bool
processed_func_p (tree func)
{
  static htab_t seen = NULL;
  void **slot;

  if (!seen)
    seen = htab_create (100, htab_hash_pointer, htab_eq_pointer, NULL);

  slot = htab_find_slot (seen, func, INSERT);
  gcc_assert (slot);

  if (*slot)
    return true;

  *slot = func;
  return false;
}