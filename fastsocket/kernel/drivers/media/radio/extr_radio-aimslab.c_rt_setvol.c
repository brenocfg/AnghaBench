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
struct rtrack {int curvol; int /*<<< orphan*/  lock; scalar_t__ muted; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_decvol (struct rtrack*) ; 
 int /*<<< orphan*/  rt_incvol (struct rtrack*) ; 
 int /*<<< orphan*/  sleep_delay (int) ; 

__attribute__((used)) static int rt_setvol(struct rtrack *rt, int vol)
{
	int i;

	mutex_lock(&rt->lock);

	if (vol == rt->curvol) {	/* requested volume = current */
		if (rt->muted) {	/* user is unmuting the card  */
			rt->muted = 0;
			outb(0xd8, rt->io);	/* enable card */
		}
		mutex_unlock(&rt->lock);
		return 0;
	}

	if (vol == 0) {			/* volume = 0 means mute the card */
		outb(0x48, rt->io);	/* volume down but still "on"	*/
		sleep_delay(2000000);	/* make sure it's totally down	*/
		outb(0xd0, rt->io);	/* volume steady, off		*/
		rt->curvol = 0;		/* track the volume state!	*/
		mutex_unlock(&rt->lock);
		return 0;
	}

	rt->muted = 0;
	if (vol > rt->curvol)
		for (i = rt->curvol; i < vol; i++)
			rt_incvol(rt);
	else
		for (i = rt->curvol; i > vol; i--)
			rt_decvol(rt);

	rt->curvol = vol;
	mutex_unlock(&rt->lock);
	return 0;
}