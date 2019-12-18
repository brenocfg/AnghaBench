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
struct pcmcia_socket {int dummy; } ;
struct pcmcia_device {int /*<<< orphan*/  suspended; struct pcmcia_socket* socket; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  runtime_resume (struct device*) ; 
 struct pcmcia_device* to_pcmcia_dev (struct device*) ; 

__attribute__((used)) static int pcmcia_bus_resume_callback(struct device *dev, void * _data)
{
	struct pcmcia_socket *skt = _data;
	struct pcmcia_device *p_dev = to_pcmcia_dev(dev);

	if (p_dev->socket != skt || !p_dev->suspended)
		return 0;

	runtime_resume(dev);

	return 0;
}