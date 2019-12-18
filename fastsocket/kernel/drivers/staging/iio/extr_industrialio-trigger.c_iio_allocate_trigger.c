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
struct TYPE_3__ {int /*<<< orphan*/ * class; int /*<<< orphan*/ * type; } ;
struct iio_trigger {int /*<<< orphan*/  pollfunc_list; int /*<<< orphan*/  list; int /*<<< orphan*/  pollfunc_list_lock; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_class ; 
 int /*<<< orphan*/  iio_get () ; 
 int /*<<< orphan*/  iio_trig_type ; 
 struct iio_trigger* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct iio_trigger *iio_allocate_trigger(void)
{
	struct iio_trigger *trig;
	trig = kzalloc(sizeof *trig, GFP_KERNEL);
	if (trig) {
		trig->dev.type = &iio_trig_type;
		trig->dev.class = &iio_class;
		device_initialize(&trig->dev);
		dev_set_drvdata(&trig->dev, (void *)trig);
		spin_lock_init(&trig->pollfunc_list_lock);
		INIT_LIST_HEAD(&trig->list);
		INIT_LIST_HEAD(&trig->pollfunc_list);
		iio_get();
	}
	return trig;
}