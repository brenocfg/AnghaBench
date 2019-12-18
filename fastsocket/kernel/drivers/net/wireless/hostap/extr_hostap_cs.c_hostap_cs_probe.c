#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  IntType; } ;
struct pcmcia_device {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXTRA ; 
 int /*<<< orphan*/  DEBUG_HW ; 
 int /*<<< orphan*/  INT_MEMORY_AND_IO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info ; 
 int prism2_config (struct pcmcia_device*) ; 

__attribute__((used)) static int hostap_cs_probe(struct pcmcia_device *p_dev)
{
	int ret;

	PDEBUG(DEBUG_HW, "%s: setting Vcc=33 (constant)\n", dev_info);
	p_dev->conf.IntType = INT_MEMORY_AND_IO;

	ret = prism2_config(p_dev);
	if (ret) {
		PDEBUG(DEBUG_EXTRA, "prism2_config() failed\n");
	}

	return ret;
}