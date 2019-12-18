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
struct pcmcia_socket {int state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 int SOCKET_SUSPEND ; 
 size_t pcmcia_resume_card (struct pcmcia_socket*) ; 
 size_t pcmcia_suspend_card (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct pcmcia_socket* to_socket (struct device*) ; 

__attribute__((used)) static ssize_t pccard_store_card_pm_state(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t count)
{
	ssize_t ret = -EINVAL;
	struct pcmcia_socket *s = to_socket(dev);

	if (!count)
		return -EINVAL;

	if (!(s->state & SOCKET_SUSPEND) && !strncmp(buf, "off", 3))
		ret = pcmcia_suspend_card(s);
	else if ((s->state & SOCKET_SUSPEND) && !strncmp(buf, "on", 2))
		ret = pcmcia_resume_card(s);

	return ret ? -ENODEV : count;
}