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
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void allocate_mostly_zero_pages(char **buf, int num_pages, int vmpgsize) {
	int i, j;

	for (i = 0; i < num_pages; i++) {
		buf[i] = (char*)malloc((size_t)vmpgsize * sizeof(char));
		memset(buf[i], 0, vmpgsize);
		for (j = 0; j < 40; j++) {
			buf[i][j] = (char)(j+1);
		}
	}
}