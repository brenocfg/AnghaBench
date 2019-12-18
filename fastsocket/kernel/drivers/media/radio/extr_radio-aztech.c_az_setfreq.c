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
struct aztech {unsigned long curfreq; int /*<<< orphan*/  lock; int /*<<< orphan*/  io; int /*<<< orphan*/  curvol; scalar_t__ stereo; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radio_wait_time ; 
 int /*<<< orphan*/  send_0_byte (struct aztech*) ; 
 int /*<<< orphan*/  send_1_byte (struct aztech*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 scalar_t__ volconvert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int az_setfreq(struct aztech *az, unsigned long frequency)
{
	int  i;

	mutex_lock(&az->lock);

	az->curfreq = frequency;
	frequency += 171200;		/* Add 10.7 MHz IF		*/
	frequency /= 800;		/* Convert to 50 kHz units	*/

	send_0_byte(az);		/*  0: LSB of frequency       */

	for (i = 0; i < 13; i++)	/*   : frequency bits (1-13)  */
		if (frequency & (1 << i))
			send_1_byte(az);
		else
			send_0_byte(az);

	send_0_byte(az);		/* 14: test bit - always 0    */
	send_0_byte(az);		/* 15: test bit - always 0    */
	send_0_byte(az);		/* 16: band data 0 - always 0 */
	if (az->stereo)		/* 17: stereo (1 to enable)   */
		send_1_byte(az);
	else
		send_0_byte(az);

	send_1_byte(az);		/* 18: band data 1 - unknown  */
	send_0_byte(az);		/* 19: time base - always 0   */
	send_0_byte(az);		/* 20: spacing (0 = 25 kHz)   */
	send_1_byte(az);		/* 21: spacing (1 = 25 kHz)   */
	send_0_byte(az);		/* 22: spacing (0 = 25 kHz)   */
	send_1_byte(az);		/* 23: AM/FM (FM = 1, always) */

	/* latch frequency */

	udelay(radio_wait_time);
	outb_p(128 + 64 + volconvert(az->curvol), az->io);

	mutex_unlock(&az->lock);

	return 0;
}