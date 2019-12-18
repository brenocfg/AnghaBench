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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ c_segment_count ; 
 scalar_t__ c_segment_pages_compressed ; 
 scalar_t__ c_segment_pages_compressed_nearing_limit ; 
 scalar_t__ c_segments_nearing_limit ; 

boolean_t
vm_compressor_low_on_space(void)
{
	if ((c_segment_pages_compressed > c_segment_pages_compressed_nearing_limit) ||
	    (c_segment_count > c_segments_nearing_limit))
		return (TRUE);

	return (FALSE);
}