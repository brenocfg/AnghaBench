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
struct rtrack {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep_delay (int) ; 

__attribute__((used)) static void rt_incvol(struct rtrack *rt)
{
	outb(0x98, rt->io);		/* volume up + sigstr + on	*/
	sleep_delay(100000);
	outb(0xd8, rt->io);		/* volume steady + sigstr + on	*/
}