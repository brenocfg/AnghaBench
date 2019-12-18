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
struct parport {int daisy; } ;
struct pardevice {int daisy; } ;
struct daisydev {int devnum; int daisy; int /*<<< orphan*/  port; struct daisydev* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  parport_claim_or_block (struct pardevice*) ; 
 struct parport* parport_get_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parport_put_port (struct parport*) ; 
 struct pardevice* parport_register_device (struct parport*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_release (struct pardevice*) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct daisydev* topology ; 
 int /*<<< orphan*/  topology_lock ; 

struct pardevice *parport_open(int devnum, const char *name)
{
	struct daisydev *p = topology;
	struct parport *port;
	struct pardevice *dev;
	int daisy;

	spin_lock(&topology_lock);
	while (p && p->devnum != devnum)
		p = p->next;

	if (!p) {
		spin_unlock(&topology_lock);
		return NULL;
	}

	daisy = p->daisy;
	port = parport_get_port(p->port);
	spin_unlock(&topology_lock);

	dev = parport_register_device(port, name, NULL, NULL, NULL, 0, NULL);
	parport_put_port(port);
	if (!dev)
		return NULL;

	dev->daisy = daisy;

	/* Check that there really is a device to select. */
	if (daisy >= 0) {
		int selected;
		parport_claim_or_block(dev);
		selected = port->daisy;
		parport_release(dev);

		if (selected != daisy) {
			/* No corresponding device. */
			parport_unregister_device(dev);
			return NULL;
		}
	}

	return dev;
}