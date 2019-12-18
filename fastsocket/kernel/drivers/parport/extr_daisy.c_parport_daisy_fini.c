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
struct parport {int dummy; } ;
struct daisydev {struct daisydev* next; struct parport* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct daisydev*) ; 
 scalar_t__ numdevs ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct daisydev* topology ; 
 int /*<<< orphan*/  topology_lock ; 

void parport_daisy_fini(struct parport *port)
{
	struct daisydev **p;

	spin_lock(&topology_lock);
	p = &topology;
	while (*p) {
		struct daisydev *dev = *p;
		if (dev->port != port) {
			p = &dev->next;
			continue;
		}
		*p = dev->next;
		kfree(dev);
	}

	/* Gaps in the numbering could be handled better.  How should
           someone enumerate through all IEEE1284.3 devices in the
           topology?. */
	if (!topology) numdevs = 0;
	spin_unlock(&topology_lock);
	return;
}