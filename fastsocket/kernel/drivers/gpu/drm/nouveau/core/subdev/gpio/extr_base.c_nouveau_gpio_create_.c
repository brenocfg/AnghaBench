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
struct nouveau_oclass {int dummy; } ;
struct nouveau_object {int dummy; } ;
struct nouveau_gpio {int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  find; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int nouveau_event_create (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_gpio_find ; 
 int /*<<< orphan*/  nouveau_gpio_get ; 
 int /*<<< orphan*/  nouveau_gpio_set ; 
 int nouveau_subdev_create_ (struct nouveau_object*,struct nouveau_object*,struct nouveau_oclass*,int /*<<< orphan*/ ,char*,char*,int,void**) ; 

int
nouveau_gpio_create_(struct nouveau_object *parent,
		     struct nouveau_object *engine,
		     struct nouveau_oclass *oclass, int lines,
		     int length, void **pobject)
{
	struct nouveau_gpio *gpio;
	int ret;

	ret = nouveau_subdev_create_(parent, engine, oclass, 0, "GPIO", "gpio",
				     length, pobject);
	gpio = *pobject;
	if (ret)
		return ret;

	ret = nouveau_event_create(lines, &gpio->events);
	if (ret)
		return ret;

	gpio->find = nouveau_gpio_find;
	gpio->set  = nouveau_gpio_set;
	gpio->get  = nouveau_gpio_get;
	return 0;
}