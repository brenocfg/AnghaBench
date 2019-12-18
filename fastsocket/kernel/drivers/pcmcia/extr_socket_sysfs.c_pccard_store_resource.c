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
struct pcmcia_socket {int resource_setup_done; int state; int /*<<< orphan*/  skt_mutex; TYPE_1__* callback; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* requery ) (struct pcmcia_socket*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 struct pcmcia_socket* to_socket (struct device*) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pccard_store_resource(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	unsigned long flags;
	struct pcmcia_socket *s = to_socket(dev);

	if (!count)
		return -EINVAL;

	spin_lock_irqsave(&s->lock, flags);
	if (!s->resource_setup_done)
		s->resource_setup_done = 1;
	spin_unlock_irqrestore(&s->lock, flags);

	mutex_lock(&s->skt_mutex);
	if ((s->callback) &&
	    (s->state & SOCKET_PRESENT) &&
	    !(s->state & SOCKET_CARDBUS)) {
		if (try_module_get(s->callback->owner)) {
			s->callback->requery(s, 0);
			module_put(s->callback->owner);
		}
	}
	mutex_unlock(&s->skt_mutex);

	return count;
}