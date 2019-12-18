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
struct object_block {int /*<<< orphan*/ * sect; } ;
typedef  int /*<<< orphan*/  section ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 scalar_t__ ggc_alloc_cleared (int) ; 
 int /*<<< orphan*/  hash_section (int /*<<< orphan*/ *) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_block_htab ; 

__attribute__((used)) static struct object_block *
get_block_for_section (section *sect)
{
  struct object_block *block;
  void **slot;

  if (sect == NULL)
    return NULL;

  slot = htab_find_slot_with_hash (object_block_htab, sect,
				   hash_section (sect), INSERT);
  block = (struct object_block *) *slot;
  if (block == NULL)
    {
      block = (struct object_block *)
	ggc_alloc_cleared (sizeof (struct object_block));
      block->sect = sect;
      *slot = block;
    }
  return block;
}