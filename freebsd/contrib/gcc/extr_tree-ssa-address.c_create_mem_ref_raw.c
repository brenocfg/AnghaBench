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
struct mem_address {void* offset; void* step; int /*<<< orphan*/  index; int /*<<< orphan*/  base; int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 void* NULL_TREE ; 
 int /*<<< orphan*/  TARGET_MEM_REF ; 
 int /*<<< orphan*/  TYPE_MODE (void*) ; 
 void* build7 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ integer_onep (void*) ; 
 int /*<<< orphan*/  valid_mem_ref_p (int /*<<< orphan*/ ,struct mem_address*) ; 
 scalar_t__ zero_p (void*) ; 

__attribute__((used)) static tree
create_mem_ref_raw (tree type, struct mem_address *addr)
{
  if (!valid_mem_ref_p (TYPE_MODE (type), addr))
    return NULL_TREE;

  if (addr->step && integer_onep (addr->step))
    addr->step = NULL_TREE;

  if (addr->offset && zero_p (addr->offset))
    addr->offset = NULL_TREE;

  return build7 (TARGET_MEM_REF, type,
		 addr->symbol, addr->base, addr->index,
		 addr->step, addr->offset, NULL, NULL);
}