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
 int /*<<< orphan*/  DTRACEIOC_ENABLE ; 
 int LEAP_DISTANCE ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,unsigned char*) ; 
 int lrand48 () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void
corrupt(int fd, unsigned char *buf, int len)
{
	static int ttl, valid;
	int bit, i;
	unsigned char saved;
	int val[LEAP_DISTANCE], pos[LEAP_DISTANCE];
	int new, rv;

again:
	printf("valid DOF #%d\n", valid++);

	/*
	 * We are going iterate through, flipping one bit and attempting
	 * to enable.
	 */
	for (bit = 0; bit < len * 8; bit++) {
		saved = buf[bit / 8];
		buf[bit / 8] ^= (1 << (bit % 8));

		if ((bit % 100) == 0)
			printf("%d\n", bit);

		if ((rv = ioctl(fd, DTRACEIOC_ENABLE, buf)) == -1) {
			/*
			 * That failed -- restore the bit and drive on.
			 */
			buf[bit / 8] = saved;
			continue;
		}

		/*
		 * That worked -- and it may have enabled probes.  To keep
		 * enabled probes down to a reasonable level, we'll close
		 * and reopen pseudodevice if we have more than 10,000
		 * probes enabled.
		 */
		ttl += rv;

		if (ttl < 10000) {
			buf[bit / 8] = saved;
			continue;
		}

		printf("enabled %d probes; resetting device.\n", ttl);
		close(fd);

		new = open("/devices/pseudo/dtrace@0:dtrace", O_RDWR);

		if (new == -1)
			fatal("couldn't open DTrace pseudo device");

		if (new != fd) {
			dup2(new, fd);
			close(new);
		}

		ttl = 0;
		buf[bit / 8] = saved;
	}

	for (;;) {
		/*
		 * Now we want to get as many bits away as possible.  We flip
		 * bits randomly -- getting as far away as we can until we don't
		 * seem to be making any progress.
		 */
		for (i = 0; i < LEAP_DISTANCE; i++) {
			/*
			 * Pick a random bit and corrupt it.
			 */
			bit = lrand48() % (len * 8);

			val[i] = buf[bit / 8];
			pos[i] = bit / 8;
			buf[bit / 8] ^= (1 << (bit % 8));
		}

		/*
		 * Let's see if that managed to get us valid DOF...
		 */
		if ((rv = ioctl(fd, DTRACEIOC_ENABLE, buf)) > 0) {
			/*
			 * Success!  This will be our new base for valid DOF.
			 */
			ttl += rv;
			goto again;
		}

		/*
		 * No luck -- we'll restore those bits and try flipping a
		 * different set.  Note that this must be done in reverse
		 * order...
		 */
		for (i = LEAP_DISTANCE - 1; i >= 0; i--)
			buf[pos[i]] = val[i];
	}
}