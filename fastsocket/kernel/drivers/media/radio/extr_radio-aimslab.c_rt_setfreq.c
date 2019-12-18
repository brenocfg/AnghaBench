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
struct rtrack {unsigned long curfreq; scalar_t__ curvol; int /*<<< orphan*/  lock; int /*<<< orphan*/  io; scalar_t__ muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_0_byte (struct rtrack*) ; 
 int /*<<< orphan*/  send_1_byte (struct rtrack*) ; 

__attribute__((used)) static int rt_setfreq(struct rtrack *rt, unsigned long freq)
{
	int i;

	mutex_lock(&rt->lock);			/* Stop other ops interfering */

	rt->curfreq = freq;

	/* now uses VIDEO_TUNER_LOW for fine tuning */

	freq += 171200;			/* Add 10.7 MHz IF 		*/
	freq /= 800;			/* Convert to 50 kHz units	*/

	send_0_byte(rt);		/*  0: LSB of frequency		*/

	for (i = 0; i < 13; i++)	/*   : frequency bits (1-13)	*/
		if (freq & (1 << i))
			send_1_byte(rt);
		else
			send_0_byte(rt);

	send_0_byte(rt);		/* 14: test bit - always 0    */
	send_0_byte(rt);		/* 15: test bit - always 0    */

	send_0_byte(rt);		/* 16: band data 0 - always 0 */
	send_0_byte(rt);		/* 17: band data 1 - always 0 */
	send_0_byte(rt);		/* 18: band data 2 - always 0 */
	send_0_byte(rt);		/* 19: time base - always 0   */

	send_0_byte(rt);		/* 20: spacing (0 = 25 kHz)   */
	send_1_byte(rt);		/* 21: spacing (1 = 25 kHz)   */
	send_0_byte(rt);		/* 22: spacing (0 = 25 kHz)   */
	send_1_byte(rt);		/* 23: AM/FM (FM = 1, always) */

	if (rt->curvol == 0 || rt->muted)
		outb(0xd0, rt->io);	/* volume steady + sigstr */
	else
		outb(0xd8, rt->io);	/* volume steady + sigstr + on */

	mutex_unlock(&rt->lock);

	return 0;
}