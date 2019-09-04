#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* memory_object_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {TYPE_1__* mo_pager_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* memory_object_terminate ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

kern_return_t memory_object_terminate
(
	memory_object_t memory_object
)
{
	return (memory_object->mo_pager_ops->memory_object_terminate)(
		memory_object);
}