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
typedef  scalar_t__ ulg ;
typedef  int /*<<< orphan*/  uch ;
struct moveparams {char* low_buffer_start; int hcount; int /*<<< orphan*/ * high_buffer_start; } ;

/* Variables and functions */
 int ALT_MEM_K ; 
 int EXT_MEM_K ; 
 scalar_t__ HEAP_SIZE ; 
 scalar_t__ LOW_BUFFER_SIZE ; 
 scalar_t__ LOW_BUFFER_START ; 
 int /*<<< orphan*/  end ; 
 int /*<<< orphan*/  error (char*) ; 
 long free_mem_end_ptr ; 
 int /*<<< orphan*/ * high_buffer_start ; 
 int high_loaded ; 
 char* output_data ; 

void setup_output_buffer_if_we_run_high(struct moveparams *mv)
{
	high_buffer_start = (uch *)(((ulg) &end) + HEAP_SIZE);
#ifdef STANDARD_MEMORY_BIOS_CALL
	if (EXT_MEM_K < (3 * 1024))
		error("Less than 4MB of memory.\n");
#else
	if ((ALT_MEM_K > EXT_MEM_K ? ALT_MEM_K : EXT_MEM_K) < (3 * 1024))
		error("Less than 4MB of memory.\n");
#endif
	mv->low_buffer_start = output_data = (char *) LOW_BUFFER_START;
	high_loaded = 1;
	free_mem_end_ptr = (long) high_buffer_start;
	if (0x100000 + LOW_BUFFER_SIZE > (ulg) high_buffer_start) {
		high_buffer_start = (uch *)(0x100000 + LOW_BUFFER_SIZE);
		mv->hcount = 0; /* say: we need not to move high_buffer */
	} else {
		mv->hcount = -1;
	}
	mv->high_buffer_start = high_buffer_start;
}