#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* remove; void* setup; int /*<<< orphan*/  class; } ;
struct TYPE_5__ {int /*<<< orphan*/ * class; } ;
struct anon_transport_class {TYPE_1__ tclass; TYPE_2__ container; } ;

/* Variables and functions */
 void* anon_transport_dummy_function ; 
 int attribute_container_register (TYPE_2__*) ; 
 int /*<<< orphan*/  attribute_container_set_no_classdevs (TYPE_2__*) ; 

int anon_transport_class_register(struct anon_transport_class *atc)
{
	int error;
	atc->container.class = &atc->tclass.class;
	attribute_container_set_no_classdevs(&atc->container);
	error = attribute_container_register(&atc->container);
	if (error)
		return error;
	atc->tclass.setup = anon_transport_dummy_function;
	atc->tclass.remove = anon_transport_dummy_function;
	return 0;
}