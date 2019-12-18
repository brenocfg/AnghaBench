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
struct wf_sensor {int /*<<< orphan*/  ref; TYPE_1__* ops; } ;
struct module {int dummy; } ;
struct TYPE_2__ {struct module* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  wf_sensor_release ; 

void wf_put_sensor(struct wf_sensor *sr)
{
	struct module *mod = sr->ops->owner;
	kref_put(&sr->ref, wf_sensor_release);
	module_put(mod);
}