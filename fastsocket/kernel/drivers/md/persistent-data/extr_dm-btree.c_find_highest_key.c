#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct ro_spine {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
struct TYPE_4__ {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * keys; TYPE_1__ header; } ;

/* Variables and functions */
 int ENODATA ; 
 int INTERNAL_NODE ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 TYPE_2__* ro_node (struct ro_spine*) ; 
 int ro_step (struct ro_spine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value64 (TYPE_2__*,int) ; 

__attribute__((used)) static int find_highest_key(struct ro_spine *s, dm_block_t block,
			    uint64_t *result_key, dm_block_t *next_block)
{
	int i, r;
	uint32_t flags;

	do {
		r = ro_step(s, block);
		if (r < 0)
			return r;

		flags = le32_to_cpu(ro_node(s)->header.flags);
		i = le32_to_cpu(ro_node(s)->header.nr_entries);
		if (!i)
			return -ENODATA;
		else
			i--;

		*result_key = le64_to_cpu(ro_node(s)->keys[i]);
		if (next_block || flags & INTERNAL_NODE)
			block = value64(ro_node(s), i);

	} while (flags & INTERNAL_NODE);

	if (next_block)
		*next_block = block;
	return 0;
}