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
struct dentry {int dummy; } ;
struct TYPE_2__ {void* start_address; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* FIXADDR_START ; 
 void* PKMAP_BASE ; 
 void* VMALLOC_END ; 
 void* VMALLOC_START ; 
 TYPE_1__* address_markers ; 
 struct dentry* debugfs_create_file (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptdump_fops ; 

__attribute__((used)) static int pt_dump_init(void)
{
	struct dentry *pe;

#ifdef CONFIG_X86_32
	/* Not a compile-time constant on x86-32 */
	address_markers[2].start_address = VMALLOC_START;
	address_markers[3].start_address = VMALLOC_END;
# ifdef CONFIG_HIGHMEM
	address_markers[4].start_address = PKMAP_BASE;
	address_markers[5].start_address = FIXADDR_START;
# else
	address_markers[4].start_address = FIXADDR_START;
# endif
#endif

	pe = debugfs_create_file("kernel_page_tables", 0600, NULL, NULL,
				 &ptdump_fops);
	if (!pe)
		return -ENOMEM;

	return 0;
}