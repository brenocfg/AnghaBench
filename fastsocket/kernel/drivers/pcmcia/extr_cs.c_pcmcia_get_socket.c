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
struct pcmcia_socket {int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pcmcia_socket* dev_get_drvdata (struct device*) ; 
 struct device* get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct pcmcia_socket * pcmcia_get_socket(struct pcmcia_socket *skt)
{
	struct device *dev = get_device(&skt->dev);
	if (!dev)
		return NULL;
	skt = dev_get_drvdata(dev);
	if (!try_module_get(skt->owner)) {
		put_device(&skt->dev);
		return NULL;
	}
	return (skt);
}