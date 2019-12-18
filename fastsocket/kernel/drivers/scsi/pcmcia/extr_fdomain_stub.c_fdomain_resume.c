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
 int /*<<< orphan*/  fdomain_16x0_bus_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fdomain_resume(struct pcmcia_device *link)
{
	fdomain_16x0_bus_reset(NULL);

	return 0;
}