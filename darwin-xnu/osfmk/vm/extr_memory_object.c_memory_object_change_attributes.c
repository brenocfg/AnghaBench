#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* old_memory_object_behave_info_t ;
typedef  TYPE_3__* old_memory_object_attr_info_t ;
typedef  TYPE_4__* memory_object_perf_info_t ;
typedef  int /*<<< orphan*/  memory_object_info_t ;
typedef  int memory_object_flavor_t ;
typedef  scalar_t__ memory_object_copy_strategy_t ;
typedef  int /*<<< orphan*/  memory_object_control_t ;
typedef  TYPE_5__* memory_object_behave_info_t ;
typedef  TYPE_6__* memory_object_attr_info_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_17__ {scalar_t__ copy_strategy; int /*<<< orphan*/  may_cache_object; } ;
struct TYPE_16__ {scalar_t__ copy_strategy; int /*<<< orphan*/  invalidate; } ;
struct TYPE_15__ {int /*<<< orphan*/  may_cache; } ;
struct TYPE_14__ {scalar_t__ copy_strategy; int /*<<< orphan*/  may_cache; } ;
struct TYPE_13__ {scalar_t__ copy_strategy; int /*<<< orphan*/  invalidate; } ;
struct TYPE_12__ {scalar_t__ copy_strategy; int /*<<< orphan*/  invalidate; int /*<<< orphan*/  can_persist; } ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
#define  MEMORY_OBJECT_ATTRIBUTE_INFO 132 
 int /*<<< orphan*/  MEMORY_OBJECT_ATTR_INFO_COUNT ; 
 int /*<<< orphan*/  MEMORY_OBJECT_BEHAVE_INFO_COUNT ; 
#define  MEMORY_OBJECT_BEHAVIOR_INFO 131 
 scalar_t__ MEMORY_OBJECT_COPY_DELAY ; 
 scalar_t__ MEMORY_OBJECT_COPY_TEMPORARY ; 
#define  MEMORY_OBJECT_PERFORMANCE_INFO 130 
 int /*<<< orphan*/  MEMORY_OBJECT_PERF_INFO_COUNT ; 
#define  OLD_MEMORY_OBJECT_ATTRIBUTE_INFO 129 
 int /*<<< orphan*/  OLD_MEMORY_OBJECT_ATTR_INFO_COUNT ; 
 int /*<<< orphan*/  OLD_MEMORY_OBJECT_BEHAVE_INFO_COUNT ; 
#define  OLD_MEMORY_OBJECT_BEHAVIOR_INFO 128 
 TYPE_1__* VM_OBJECT_NULL ; 
 TYPE_1__* memory_object_control_to_vm_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_lock (TYPE_1__*) ; 
 scalar_t__ vm_object_set_attributes_common (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vm_object_unlock (TYPE_1__*) ; 

kern_return_t
memory_object_change_attributes(
	memory_object_control_t		control,
	memory_object_flavor_t		flavor,
	memory_object_info_t		attributes,
	mach_msg_type_number_t		count)
{
	vm_object_t             	object;
	kern_return_t   		result = KERN_SUCCESS;
	boolean_t       		may_cache;
	boolean_t       		invalidate;
	memory_object_copy_strategy_t	copy_strategy;

	object = memory_object_control_to_vm_object(control);
	if (object == VM_OBJECT_NULL)
		return (KERN_INVALID_ARGUMENT);

	vm_object_lock(object);

	may_cache = object->can_persist;
	copy_strategy = object->copy_strategy;
#if notyet
	invalidate = object->invalidate;
#endif
	vm_object_unlock(object);	

	switch (flavor) {
	    case OLD_MEMORY_OBJECT_BEHAVIOR_INFO:
	    {
                old_memory_object_behave_info_t     behave;

                if (count != OLD_MEMORY_OBJECT_BEHAVE_INFO_COUNT) {
                        result = KERN_INVALID_ARGUMENT;
                        break;
                }

                behave = (old_memory_object_behave_info_t) attributes;

		invalidate = behave->invalidate;
		copy_strategy = behave->copy_strategy;

		break;
	    }

	    case MEMORY_OBJECT_BEHAVIOR_INFO:
	    {
                memory_object_behave_info_t     behave;

                if (count != MEMORY_OBJECT_BEHAVE_INFO_COUNT) {
                        result = KERN_INVALID_ARGUMENT;
                        break;
                }

                behave = (memory_object_behave_info_t) attributes;

		invalidate = behave->invalidate;
		copy_strategy = behave->copy_strategy;
		break;
	    }

	    case MEMORY_OBJECT_PERFORMANCE_INFO:
	    {
		memory_object_perf_info_t	perf;

                if (count != MEMORY_OBJECT_PERF_INFO_COUNT) {
                        result = KERN_INVALID_ARGUMENT;
                        break;
                }

                perf = (memory_object_perf_info_t) attributes;

		may_cache = perf->may_cache;

		break;
	    }

	    case OLD_MEMORY_OBJECT_ATTRIBUTE_INFO:
	    {
		old_memory_object_attr_info_t	attr;

                if (count != OLD_MEMORY_OBJECT_ATTR_INFO_COUNT) {
                        result = KERN_INVALID_ARGUMENT;
                        break;
                }

		attr = (old_memory_object_attr_info_t) attributes;

                may_cache = attr->may_cache;
                copy_strategy = attr->copy_strategy;

		break;
	    }

	    case MEMORY_OBJECT_ATTRIBUTE_INFO:
	    {
		memory_object_attr_info_t	attr;

                if (count != MEMORY_OBJECT_ATTR_INFO_COUNT) {
                        result = KERN_INVALID_ARGUMENT;
                        break;
                }

		attr = (memory_object_attr_info_t) attributes;

		copy_strategy = attr->copy_strategy;
                may_cache = attr->may_cache_object;

		break;
	    }

	    default:
		result = KERN_INVALID_ARGUMENT;
		break;
	}

	if (result != KERN_SUCCESS)
		return(result);

	if (copy_strategy == MEMORY_OBJECT_COPY_TEMPORARY) {
		copy_strategy = MEMORY_OBJECT_COPY_DELAY;
	}

	/*
	 * XXX	may_cache may become a tri-valued variable to handle
	 * XXX	uncache if not in use.
	 */
	return (vm_object_set_attributes_common(object,
						     may_cache,
						     copy_strategy));
}