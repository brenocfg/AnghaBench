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
typedef  int /*<<< orphan*/ * tree ;
struct function {int /*<<< orphan*/ * used_types_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/ * htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_eq_pointer ; 
 void** htab_find_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer ; 

__attribute__((used)) static void
used_types_insert_helper (tree type, struct function *func)
{
  if (type != NULL && func != NULL)
    {
      void **slot;

      if (func->used_types_hash == NULL)
	func->used_types_hash = htab_create_ggc (37, htab_hash_pointer,
						 htab_eq_pointer, NULL);
      slot = htab_find_slot (func->used_types_hash, type, INSERT);
      if (*slot == NULL)
	*slot = type;
    }
}