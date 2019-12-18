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
struct pcmcia_socket {int /*<<< orphan*/  socket_released; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct pcmcia_socket* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void pcmcia_release_socket(struct device *dev)
{
	struct pcmcia_socket *socket = dev_get_drvdata(dev);

	complete(&socket->socket_released);
}