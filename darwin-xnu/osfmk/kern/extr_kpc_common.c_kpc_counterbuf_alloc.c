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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTERBUF_SIZE ; 
 int /*<<< orphan*/  VM_KERN_MEMORY_DIAG ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kalloc_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t *
kpc_counterbuf_alloc(void)
{
	uint64_t *buf = NULL;

	buf = kalloc_tag(COUNTERBUF_SIZE, VM_KERN_MEMORY_DIAG);
	if (buf) {
		bzero(buf, COUNTERBUF_SIZE);
	}

	return buf;
}