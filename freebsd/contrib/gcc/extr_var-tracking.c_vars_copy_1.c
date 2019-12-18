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
typedef  TYPE_1__* variable ;
typedef  int /*<<< orphan*/  htab_t ;
struct TYPE_2__ {int /*<<< orphan*/  decl; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  VARIABLE_HASH_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vars_copy_1 (void **slot, void *data)
{
  htab_t dst = (htab_t) data;
  variable src, *dstp;

  src = *(variable *) slot;
  src->refcount++;

  dstp = (variable *) htab_find_slot_with_hash (dst, src->decl,
						VARIABLE_HASH_VAL (src->decl),
						INSERT);
  *dstp = src;

  /* Continue traversing the hash table.  */
  return 1;
}