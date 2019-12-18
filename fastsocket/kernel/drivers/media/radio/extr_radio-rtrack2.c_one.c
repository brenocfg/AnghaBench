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

__attribute__((used)) static void one(struct rtrack2 *dev)
{
	outb_p(5, dev->io);
	outb_p(7, dev->io);
	outb_p(5, dev->io);
}