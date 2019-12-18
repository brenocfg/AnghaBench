#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mach_port_index_t ;
typedef  TYPE_1__* ipc_space_t ;
typedef  TYPE_2__* ipc_entry_t ;
typedef  scalar_t__ ipc_entry_num_t ;
struct TYPE_6__ {void* ie_bits; scalar_t__ ie_index; void* ie_object; scalar_t__ ie_next; } ;
struct TYPE_5__ {int /*<<< orphan*/ * is_entropy; int /*<<< orphan*/  bool_gen; } ;

/* Variables and functions */
 void* IE_BITS_GEN_MASK ; 
 void* IO_NULL ; 
 int /*<<< orphan*/  IS_ENTROPY_CNT ; 
 scalar_t__ NUM_SEQ_ENTRIES ; 
 int random_bool_gen_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
ipc_space_rand_freelist(
	ipc_space_t		space,
	ipc_entry_t		table,
	mach_port_index_t	bottom,
	mach_port_index_t	top)
{
	int at_start = (bottom == 0);
#ifdef CONFIG_SEMI_RANDOM_ENTRIES
	/*
	 * Only make sequential entries at the start of the table, and not when
	 * we're growing the space.
	 */
	ipc_entry_num_t total = 0;
#endif

	/* First entry in the free list is always free, and is the start of the free list. */
	mach_port_index_t curr = bottom;
	bottom++;
	top--;

	/*
	 *	Initialize the free list in the table.
	 *	Add the entries in pseudo-random order and randomly set the generation
	 *	number, in order to frustrate attacks involving port name reuse.
	 */
	while (bottom <= top) {
		ipc_entry_t entry = &table[curr];
		int which;
#ifdef CONFIG_SEMI_RANDOM_ENTRIES
		/*
		 * XXX: This is a horrible hack to make sure that randomizing the port
		 * doesn't break programs that might have (sad) hard-coded values for
		 * certain port names.
		 */
		if (at_start && total++ < NUM_SEQ_ENTRIES)
			which = 0;
		else
#endif
			which = random_bool_gen_bits(
						&space->bool_gen,
						&space->is_entropy[0],
						IS_ENTROPY_CNT,
						1);

		mach_port_index_t next;
		if (which) {
			next = top;
			top--;
		} else {
			next = bottom;
			bottom++;
		}

		/*
		 * The entry's gencount will roll over on its first allocation, at which
		 * point a random rollover will be set for the entry.
		 */
		entry->ie_bits = IE_BITS_GEN_MASK;
		entry->ie_next   = next;
		entry->ie_object = IO_NULL;
		entry->ie_index  = 0;
		curr = next;
	}
	table[curr].ie_next   = 0;
	table[curr].ie_object = IO_NULL;
	table[curr].ie_index  = 0;
	table[curr].ie_bits   = IE_BITS_GEN_MASK;

	/* The freelist head should always have generation number set to 0 */
	if (at_start) {
		table[0].ie_bits = 0;
	}
}