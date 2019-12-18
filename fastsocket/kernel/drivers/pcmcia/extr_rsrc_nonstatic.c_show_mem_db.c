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
struct resource_map {scalar_t__ num; scalar_t__ base; struct resource_map* next; } ;
struct socket_data {struct resource_map mem_db; } ;
struct pcmcia_socket {struct socket_data* resource_data; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 struct pcmcia_socket* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsrc_mutex ; 
 scalar_t__ snprintf (char*,int,char*,unsigned long,scalar_t__) ; 

__attribute__((used)) static ssize_t show_mem_db(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct pcmcia_socket *s = dev_get_drvdata(dev);
	struct socket_data *data;
	struct resource_map *p;
	ssize_t ret = 0;

	mutex_lock(&rsrc_mutex);
	data = s->resource_data;

	for (p = data->mem_db.next; p != &data->mem_db; p = p->next) {
		if (ret > (PAGE_SIZE - 10))
			continue;
		ret += snprintf (&buf[ret], (PAGE_SIZE - ret - 1),
				 "0x%08lx - 0x%08lx\n",
				 ((unsigned long) p->base),
				 ((unsigned long) p->base + p->num - 1));
	}

	mutex_unlock(&rsrc_mutex);
	return (ret);
}