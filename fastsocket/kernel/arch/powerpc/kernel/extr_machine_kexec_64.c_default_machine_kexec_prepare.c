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
struct kimage {int nr_segments; TYPE_1__* segment; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  hpte_clear_all; } ;
struct TYPE_3__ {unsigned long mem; unsigned long memsz; } ;

/* Variables and functions */
 int ENOENT ; 
 int ETXTBSY ; 
 unsigned long __pa (scalar_t__) ; 
 scalar_t__ _end ; 
 scalar_t__ htab_address ; 
 unsigned long htab_size_bytes ; 
 struct device_node* of_find_node_by_type (struct device_node*,char*) ; 
 void* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__ ppc_md ; 

int default_machine_kexec_prepare(struct kimage *image)
{
	int i;
	unsigned long begin, end;	/* limits of segment */
	unsigned long low, high;	/* limits of blocked memory range */
	struct device_node *node;
	const unsigned long *basep;
	const unsigned int *sizep;

	if (!ppc_md.hpte_clear_all)
		return -ENOENT;

	/*
	 * Since we use the kernel fault handlers and paging code to
	 * handle the virtual mode, we must make sure no destination
	 * overlaps kernel static data or bss.
	 */
	for (i = 0; i < image->nr_segments; i++)
		if (image->segment[i].mem < __pa(_end))
			return -ETXTBSY;

	/*
	 * For non-LPAR, we absolutely can not overwrite the mmu hash
	 * table, since we are still using the bolted entries in it to
	 * do the copy.  Check that here.
	 *
	 * It is safe if the end is below the start of the blocked
	 * region (end <= low), or if the beginning is after the
	 * end of the blocked region (begin >= high).  Use the
	 * boolean identity !(a || b)  === (!a && !b).
	 */
	if (htab_address) {
		low = __pa(htab_address);
		high = low + htab_size_bytes;

		for (i = 0; i < image->nr_segments; i++) {
			begin = image->segment[i].mem;
			end = begin + image->segment[i].memsz;

			if ((begin < high) && (end > low))
				return -ETXTBSY;
		}
	}

	/* We also should not overwrite the tce tables */
	for (node = of_find_node_by_type(NULL, "pci"); node != NULL;
			node = of_find_node_by_type(node, "pci")) {
		basep = of_get_property(node, "linux,tce-base", NULL);
		sizep = of_get_property(node, "linux,tce-size", NULL);
		if (basep == NULL || sizep == NULL)
			continue;

		low = *basep;
		high = low + (*sizep);

		for (i = 0; i < image->nr_segments; i++) {
			begin = image->segment[i].mem;
			end = begin + image->segment[i].memsz;

			if ((begin < high) && (end > low))
				return -ETXTBSY;
		}
	}

	return 0;
}