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
struct TYPE_2__ {int Vcc; } ;
struct pcmcia_socket {int state; TYPE_1__ socket; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 struct pcmcia_socket* to_socket (struct device*) ; 

__attribute__((used)) static ssize_t pccard_show_vcc(struct device *dev, struct device_attribute *attr,
			       char *buf)
{
	struct pcmcia_socket *s = to_socket(dev);
	if (!(s->state & SOCKET_PRESENT))
		return -ENODEV;
	return sprintf(buf, "%d.%dV\n", s->socket.Vcc / 10, s->socket.Vcc % 10);
}