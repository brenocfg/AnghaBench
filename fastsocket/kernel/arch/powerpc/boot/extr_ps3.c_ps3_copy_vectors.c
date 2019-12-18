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
 int /*<<< orphan*/  flush_cache (void*,int) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 

void ps3_copy_vectors(void)
{
	extern char __system_reset_kernel[];

	memcpy((void *)0x100, __system_reset_kernel, 512);
	flush_cache((void *)0x100, 512);
}