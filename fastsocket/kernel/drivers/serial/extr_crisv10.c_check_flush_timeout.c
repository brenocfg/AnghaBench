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
struct e100_serial {scalar_t__ first_recv_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  START_FLUSH_FAST_TIMER_TIME (struct e100_serial*,char*,int) ; 
 int /*<<< orphan*/  flush_to_flip_buffer (struct e100_serial*) ; 
 int /*<<< orphan*/  force_eop_if_needed (struct e100_serial*) ; 

__attribute__((used)) static void check_flush_timeout(struct e100_serial *info)
{
	/* Flip what we've got (if we can) */
	flush_to_flip_buffer(info);

	/* We might need to flip later, but not to fast
	 * since the system is busy processing input... */
	if (info->first_recv_buffer)
		START_FLUSH_FAST_TIMER_TIME(info, "flip", 2000);

	/* Force eop last, since data might have come while we're processing
	 * and if we started the slow timer above, we won't start a fast
	 * below.
	 */
	force_eop_if_needed(info);
}