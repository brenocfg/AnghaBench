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
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

void ecryptfs_to_hex(char *dst, char *src, size_t src_size)
{
	int x;

	for (x = 0; x < src_size; x++)
		sprintf(&dst[x * 2], "%.2x", (unsigned char)src[x]);
}