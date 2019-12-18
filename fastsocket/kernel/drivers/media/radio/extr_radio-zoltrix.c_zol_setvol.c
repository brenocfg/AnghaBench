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
struct zoltrix {int curvol; int /*<<< orphan*/  lock; scalar_t__ io; scalar_t__ muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int zol_setvol(struct zoltrix *zol, int vol)
{
	zol->curvol = vol;
	if (zol->muted)
		return 0;

	mutex_lock(&zol->lock);
	if (vol == 0) {
		outb(0, zol->io);
		outb(0, zol->io);
		inb(zol->io + 3);    /* Zoltrix needs to be read to confirm */
		mutex_unlock(&zol->lock);
		return 0;
	}

	outb(zol->curvol-1, zol->io);
	msleep(10);
	inb(zol->io + 2);
	mutex_unlock(&zol->lock);
	return 0;
}