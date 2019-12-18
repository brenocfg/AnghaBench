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
 int /*<<< orphan*/  arc4random_buf (void*,size_t) ; 
 scalar_t__ malloc (size_t) ; 

void allocate_random_pages(char **buf, int num_pages, int vmpgsize) {
	int i;

	for (i = 0; i < num_pages; i++) {
		buf[i] = (char*)malloc((size_t)vmpgsize * sizeof(char));
		arc4random_buf((void*)buf[i], (size_t)vmpgsize);
	}
}