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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  ioc ;
typedef  scalar_t__ hrtime_t ;
typedef  unsigned int* caddr_t ;

/* Variables and functions */
 unsigned int DTRACEIOC ; 
 unsigned int DTRACEIOC_MAX ; 
 scalar_t__ ESRCH ; 
 int MAP_ANON ; 
 int MAP_PRIVATE ; 
 scalar_t__ NANOSEC ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  ioctl (int,unsigned int,unsigned int*) ; 
 int kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int* mmap (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,unsigned int*,int) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

void
badioctl(pid_t parent)
{
	int fd = -1, random, ps = sysconf(_SC_PAGESIZE);
	int i = 0, seconds;
	caddr_t addr;
	hrtime_t now, last = 0, end;

	if ((random = open("/dev/random", O_RDONLY)) == -1)
		fatal("couldn't open /dev/random");

	if ((addr = mmap(0, ps, PROT_READ | PROT_WRITE,
	    MAP_ANON | MAP_PRIVATE, -1, 0)) == (caddr_t)-1)
		fatal("mmap");

	for (;;) {
		unsigned int ioc;

		if ((now = gethrtime()) - last > NANOSEC) {
			if (kill(parent, 0) == -1 && errno == ESRCH) {
				/*
				 * Our parent died.  We will kill ourselves in
				 * sympathy.
				 */
				exit(0);
			}

			/*
			 * Once a second, we'll reopen the device.
			 */
			if (fd != -1)
				close(fd);

			fd = open("/devices/pseudo/dtrace@0:dtrace", O_RDONLY);

			if (fd == -1)
				fatal("couldn't open DTrace pseudo device");

			last = now;
		}


		if ((i++ % 1000) == 0) {
			/*
			 * Every thousand iterations, change our random gunk.
			 */
			read(random, addr, ps);
		}

		read(random, &ioc, sizeof (ioc));
		ioc %= DTRACEIOC_MAX;
		ioc++;
		ioctl(fd, DTRACEIOC | ioc, addr);
	}
}