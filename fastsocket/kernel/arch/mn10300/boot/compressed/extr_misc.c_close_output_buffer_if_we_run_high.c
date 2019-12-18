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
struct moveparams {scalar_t__ hcount; scalar_t__ lcount; } ;

/* Variables and functions */
 scalar_t__ LOW_BUFFER_SIZE ; 
 scalar_t__ bytes_out ; 

void close_output_buffer_if_we_run_high(struct moveparams *mv)
{
	mv->lcount = bytes_out;
	if (bytes_out > LOW_BUFFER_SIZE) {
		mv->lcount = LOW_BUFFER_SIZE;
		if (mv->hcount)
			mv->hcount = bytes_out - LOW_BUFFER_SIZE;
	} else {
		mv->hcount = 0;
	}
}