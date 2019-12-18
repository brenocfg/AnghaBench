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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int mixerdev ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 

int sndout_oss_init(void)
{
	if (mixerdev >= 0) close(mixerdev);
  	mixerdev = open("/dev/mixer", O_RDWR);
	if (mixerdev == -1)
	{
		perror("open(\"/dev/mixer\")");
	}

	return 0;
}