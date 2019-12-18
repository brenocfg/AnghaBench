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
struct trust {unsigned long curfreq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSA6060T_ADDR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_i2c (struct trust*,int,int /*<<< orphan*/ ,unsigned long,unsigned long,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tr_setfreq(struct trust *tr, unsigned long f)
{
	mutex_lock(&tr->lock);
	tr->curfreq = f;
	f /= 160;	/* Convert to 10 kHz units	*/
	f += 1070;	/* Add 10.7 MHz IF		*/
	write_i2c(tr, 5, TSA6060T_ADDR, (f << 1) | 1, f >> 7, 0x60 | ((f >> 15) & 1), 0);
	mutex_unlock(&tr->lock);
}