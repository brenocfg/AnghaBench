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
struct pcmcia_device {int /*<<< orphan*/ * priv; } ;
typedef  int /*<<< orphan*/  btuart_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  btuart_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

__attribute__((used)) static void btuart_release(struct pcmcia_device *link)
{
	btuart_info_t *info = link->priv;

	btuart_close(info);

	pcmcia_disable_device(link);
}