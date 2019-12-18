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
struct zoltrix {int curvol; int /*<<< orphan*/  lock; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zol_is_stereo(struct zoltrix *zol)
{
	int x1, x2;

	mutex_lock(&zol->lock);

	outb(0x00, zol->io);
	outb(zol->curvol, zol->io);
	msleep(20);

	x1 = inb(zol->io);
	msleep(10);
	x2 = inb(zol->io);

	mutex_unlock(&zol->lock);

	return x1 == x2 && x1 == 0xcf;
}