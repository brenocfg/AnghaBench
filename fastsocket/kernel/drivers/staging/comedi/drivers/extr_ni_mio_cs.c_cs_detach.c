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
struct pcmcia_device {scalar_t__ dev_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  cs_release (struct pcmcia_device*) ; 

__attribute__((used)) static void cs_detach(struct pcmcia_device *link)
{
	DPRINTK("cs_detach(link=%p)\n", link);

	if (link->dev_node) {
		cs_release(link);
	}
}