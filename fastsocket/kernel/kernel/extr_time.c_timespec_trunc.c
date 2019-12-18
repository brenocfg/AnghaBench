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
struct timespec {unsigned int tv_nsec; } ;

/* Variables and functions */
 int jiffies_to_usecs (int) ; 

struct timespec timespec_trunc(struct timespec t, unsigned gran)
{
	/*
	 * Division is pretty slow so avoid it for common cases.
	 * Currently current_kernel_time() never returns better than
	 * jiffies resolution. Exploit that.
	 */
	if (gran <= jiffies_to_usecs(1) * 1000) {
		/* nothing */
	} else if (gran == 1000000000) {
		t.tv_nsec = 0;
	} else {
		t.tv_nsec -= t.tv_nsec % gran;
	}
	return t;
}