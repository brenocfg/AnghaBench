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
struct fmi {unsigned long curfreq; scalar_t__ curvol; int /*<<< orphan*/  lock; int /*<<< orphan*/  io; } ;

/* Variables and functions */
 int RSF16_ENCODE (unsigned long) ; 
 int /*<<< orphan*/  fmi_unmute (struct fmi*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outbits (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fmi_setfreq(struct fmi *fmi, unsigned long freq)
{
	mutex_lock(&fmi->lock);
	fmi->curfreq = freq;

	outbits(16, RSF16_ENCODE(freq), fmi->io);
	outbits(8, 0xC0, fmi->io);
	msleep(143);		/* was schedule_timeout(HZ/7) */
	mutex_unlock(&fmi->lock);
	if (fmi->curvol)
		fmi_unmute(fmi);
	return 0;
}