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
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ pcmcia_dev_present (struct pcmcia_device*) ; 

__attribute__((used)) static int card_present(void *arg)
{
	struct pcmcia_device *link = (struct pcmcia_device *)arg;

	if (pcmcia_dev_present(link))
		return 1;

	return 0;
}