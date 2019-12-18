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
struct qcam_device {int dummy; } ;

/* Variables and functions */
 int maxpoll ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int read_lpstatus (struct qcam_device*) ; 

__attribute__((used)) static int qc_waithand(struct qcam_device *q, int val)
{
	int status;
	int runs=0;

	if (val)
	{
		while (!((status = read_lpstatus(q)) & 8))
		{
			/* 1000 is enough spins on the I/O for all normal
			   cases, at that point we start to poll slowly
			   until the camera wakes up. However, we are
			   busy blocked until the camera responds, so
			   setting it lower is much better for interactive
			   response. */

			if(runs++>maxpoll)
			{
				msleep_interruptible(5);
			}
			if(runs>(maxpoll+1000)) /* 5 seconds */
				return -1;
		}
	}
	else
	{
		while (((status = read_lpstatus(q)) & 8))
		{
			/* 1000 is enough spins on the I/O for all normal
			   cases, at that point we start to poll slowly
			   until the camera wakes up. However, we are
			   busy blocked until the camera responds, so
			   setting it lower is much better for interactive
			   response. */

			if(runs++>maxpoll)
			{
				msleep_interruptible(5);
			}
			if(runs++>(maxpoll+1000)) /* 5 seconds */
				return -1;
		}
	}

	return status;
}