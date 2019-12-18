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
typedef  int /*<<< orphan*/  snd_wavefront_t ;

/* Variables and functions */
 int HZ ; 
 int sleep_interval ; 
 int sleep_tries ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wait_usecs ; 
 scalar_t__ wavefront_sleep (int) ; 
 int wavefront_status (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wavefront_wait (snd_wavefront_t *dev, int mask)

{
	int             i;

	/* Spin for a short period of time, because >99% of all
	   requests to the WaveFront can be serviced inline like this.
	*/

	for (i = 0; i < wait_usecs; i += 5) {
		if (wavefront_status (dev) & mask) {
			return 1;
		}
		udelay(5);
	}

	for (i = 0; i < sleep_tries; i++) {

		if (wavefront_status (dev) & mask) {
			return 1;
		}

		if (wavefront_sleep (HZ/sleep_interval)) {
			return (0);
		}
	}

	return (0);
}