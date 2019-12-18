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
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 int HZ ; 
 int /*<<< orphan*/  NR_UNSTABLE_NFS ; 
 int /*<<< orphan*/  NR_WRITEBACK ; 
 int __GFP_FS ; 
 int __GFP_IO ; 
 int /*<<< orphan*/  congestion_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_dirty_limits (unsigned long*,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long global_page_state (int /*<<< orphan*/ ) ; 

void throttle_vm_writeout(gfp_t gfp_mask)
{
	unsigned long background_thresh;
	unsigned long dirty_thresh;

        for ( ; ; ) {
		get_dirty_limits(&background_thresh, &dirty_thresh, NULL, NULL);

                /*
                 * Boost the allowable dirty threshold a bit for page
                 * allocators so they don't get DoS'ed by heavy writers
                 */
                dirty_thresh += dirty_thresh / 10;      /* wheeee... */

                if (global_page_state(NR_UNSTABLE_NFS) +
			global_page_state(NR_WRITEBACK) <= dirty_thresh)
                        	break;
                congestion_wait(BLK_RW_ASYNC, HZ/10);

		/*
		 * The caller might hold locks which can prevent IO completion
		 * or progress in the filesystem.  So we cannot just sit here
		 * waiting for IO to complete.
		 */
		if ((gfp_mask & (__GFP_FS|__GFP_IO)) != (__GFP_FS|__GFP_IO))
			break;
        }
}