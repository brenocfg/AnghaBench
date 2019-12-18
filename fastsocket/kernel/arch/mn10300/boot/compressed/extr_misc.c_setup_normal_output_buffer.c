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
 int ALT_MEM_K ; 
 int EXT_MEM_K ; 
 int /*<<< orphan*/  error (char*) ; 
 char* output_data ; 

void setup_normal_output_buffer(void)
{
#ifdef STANDARD_MEMORY_BIOS_CALL
	if (EXT_MEM_K < 1024)
		error("Less than 2MB of memory.\n");
#else
	if ((ALT_MEM_K > EXT_MEM_K ? ALT_MEM_K : EXT_MEM_K) < 1024)
		error("Less than 2MB of memory.\n");
#endif
	output_data = (char *) 0x100000; /* Points to 1M */
}