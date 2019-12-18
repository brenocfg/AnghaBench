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

/* Variables and functions */
 int /*<<< orphan*/  PAGE_IO ; 
 int /*<<< orphan*/  PAGE_IO_SIZE ; 
 scalar_t__ all_mtd ; 
 int /*<<< orphan*/  del_mtd_partitions (scalar_t__) ; 
 int /*<<< orphan*/  iomapadr ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_sbc_gxx(void)
{
	if( all_mtd ) {
		del_mtd_partitions( all_mtd );
		map_destroy( all_mtd );
	}

	iounmap(iomapadr);
	release_region(PAGE_IO,PAGE_IO_SIZE);
}