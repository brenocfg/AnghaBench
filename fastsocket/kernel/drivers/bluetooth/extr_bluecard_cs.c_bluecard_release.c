#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {TYPE_1__* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ bluecard_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  bluecard_close (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void bluecard_release(struct pcmcia_device *link)
{
	bluecard_info_t *info = link->priv;

	bluecard_close(info);

	del_timer(&(info->timer));

	pcmcia_disable_device(link);
}