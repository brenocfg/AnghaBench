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
typedef  int /*<<< orphan*/  seed ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 uintptr_t getpid () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned int*,int) ; 
 int /*<<< orphan*/  srandom (unsigned int) ; 
 uintptr_t time (int /*<<< orphan*/ *) ; 

void
init_random(void)
{
	unsigned int seed;
	int rf;

	rf = open("/dev/urandom", O_RDONLY);
	if (rf == -1)
		rf = open("/dev/random", O_RDONLY);

	if (!(rf != -1 && read(rf, &seed, sizeof(seed)) == sizeof(seed)))
		seed = (time(NULL) ^ getpid()) + (uintptr_t)&seed;

	srandom(seed);

	if (rf != -1)
		close(rf);
}