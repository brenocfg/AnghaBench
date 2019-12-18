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
struct rtrack2 {int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zero(struct rtrack2 *dev)
{
	outb_p(1, dev->io);
	outb_p(3, dev->io);
	outb_p(1, dev->io);
}