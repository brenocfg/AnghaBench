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
typedef  int /*<<< orphan*/  pmap_io_range_t ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 int DTGetProperty (int /*<<< orphan*/ ,char*,void**,unsigned int*) ; 
 int DTLookupEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp_io_rgns ; 
 int /*<<< orphan*/ * io_attr_table ; 
 int kSuccess ; 
 scalar_t__ num_io_rgns ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_load_io_rgns(void)
{
	DTEntry entry;
	pmap_io_range_t *ranges;
	void *prop = NULL;
        int err;
	unsigned int prop_size;

	if (num_io_rgns == 0)
		return;

	err = DTLookupEntry(NULL, "/defaults", &entry);
	assert(err == kSuccess);

	err = DTGetProperty(entry, "pmap-io-ranges", &prop, &prop_size);
	assert(err == kSuccess);

	ranges = prop;
	for (unsigned int i = 0; i < (prop_size / sizeof(*ranges)); ++i)
		io_attr_table[i] = ranges[i];

	qsort(io_attr_table, num_io_rgns, sizeof(*ranges), cmp_io_rgns);
}