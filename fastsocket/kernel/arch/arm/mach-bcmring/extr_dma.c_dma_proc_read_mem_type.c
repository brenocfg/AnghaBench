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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gDmaStatMemTypeCoherent ; 
 int /*<<< orphan*/  gDmaStatMemTypeKmalloc ; 
 int /*<<< orphan*/  gDmaStatMemTypeUser ; 
 int /*<<< orphan*/  gDmaStatMemTypeVmalloc ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int dma_proc_read_mem_type(char *buf, char **start, off_t offset,
				  int count, int *eof, void *data)
{
	int len = 0;

	len += sprintf(buf + len, "dma_map_mem statistics\n");
	len +=
	    sprintf(buf + len, "coherent: %d\n",
		    atomic_read(&gDmaStatMemTypeCoherent));
	len +=
	    sprintf(buf + len, "kmalloc:  %d\n",
		    atomic_read(&gDmaStatMemTypeKmalloc));
	len +=
	    sprintf(buf + len, "vmalloc:  %d\n",
		    atomic_read(&gDmaStatMemTypeVmalloc));
	len +=
	    sprintf(buf + len, "user:     %d\n",
		    atomic_read(&gDmaStatMemTypeUser));

	return len;
}