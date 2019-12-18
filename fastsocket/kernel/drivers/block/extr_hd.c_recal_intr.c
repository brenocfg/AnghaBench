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
 int /*<<< orphan*/  check_status () ; 
 int /*<<< orphan*/  hd_request () ; 
 int /*<<< orphan*/  last_req ; 
 int /*<<< orphan*/  read_timer () ; 

__attribute__((used)) static void recal_intr(void)
{
	check_status();
#if (HD_DELAY > 0)
	last_req = read_timer();
#endif
	hd_request();
}