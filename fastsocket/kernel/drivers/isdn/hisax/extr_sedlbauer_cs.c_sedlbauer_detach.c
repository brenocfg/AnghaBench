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
struct pcmcia_device {scalar_t__ priv; } ;
struct TYPE_2__ {int stop; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,struct pcmcia_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  sedlbauer_release (struct pcmcia_device*) ; 

__attribute__((used)) static void sedlbauer_detach(struct pcmcia_device *link)
{
	DEBUG(0, "sedlbauer_detach(0x%p)\n", link);

	((local_info_t *)link->priv)->stop = 1;
	sedlbauer_release(link);

	/* This points to the parent local_info_t struct */
	kfree(link->priv);
}