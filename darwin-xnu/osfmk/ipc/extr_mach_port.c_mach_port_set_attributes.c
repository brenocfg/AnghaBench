#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  natural_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
struct TYPE_8__ {int /*<<< orphan*/  mpl_qlimit; } ;
typedef  TYPE_1__ mach_port_limits_t ;
typedef  scalar_t__ mach_port_info_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_2__* ipc_port_t ;
typedef  int /*<<< orphan*/  ipc_importance_task_t ;
struct TYPE_10__ {int /*<<< orphan*/  task_imp_base; } ;
struct TYPE_9__ {int ip_tempowner; int ip_impdonation; int /*<<< orphan*/  ip_specialreply; int /*<<< orphan*/  ip_impcount; int /*<<< orphan*/  ip_imp_task; int /*<<< orphan*/  ip_messages; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIT_NULL ; 
 scalar_t__ IS_NULL ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_RIGHT ; 
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  KERN_INVALID_VALUE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  MACH_PORT_DENAP_RECEIVER 132 
#define  MACH_PORT_DNREQUESTS_SIZE 131 
 int /*<<< orphan*/  MACH_PORT_DNREQUESTS_SIZE_COUNT ; 
#define  MACH_PORT_IMPORTANCE_RECEIVER 130 
#define  MACH_PORT_LIMITS_INFO 129 
 int /*<<< orphan*/  MACH_PORT_LIMITS_INFO_COUNT ; 
 int /*<<< orphan*/  MACH_PORT_QLIMIT_MAX ; 
#define  MACH_PORT_TEMPOWNER 128 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_7__* current_task () ; 
 int /*<<< orphan*/  ip_kotype (TYPE_2__*) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_importance_task_drop_internal_assertion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_task_is_any_receiver_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_importance_task_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_mqueue_set_qlimit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_request_grow (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ipc_port_translate_receive (scalar_t__,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  is_ipc_kobject (int /*<<< orphan*/ ) ; 

kern_return_t
mach_port_set_attributes(
	ipc_space_t		space,
	mach_port_name_t	name,
	int			flavor,
        mach_port_info_t	info,
        mach_msg_type_number_t	count)
{
	ipc_port_t port;
	kern_return_t kr;
        
	if (space == IS_NULL)
		return KERN_INVALID_TASK;

        switch (flavor) {
                
        case MACH_PORT_LIMITS_INFO: {
                mach_port_limits_t *mplp = (mach_port_limits_t *)info;
                
                if (count < MACH_PORT_LIMITS_INFO_COUNT)
                        return KERN_FAILURE;
                
                if (mplp->mpl_qlimit > MACH_PORT_QLIMIT_MAX)
                        return KERN_INVALID_VALUE;

		if (!MACH_PORT_VALID(name))
			return KERN_INVALID_RIGHT;

                kr = ipc_port_translate_receive(space, name, &port);
                if (kr != KERN_SUCCESS)
                        return kr;
                /* port is locked and active */

                ipc_mqueue_set_qlimit(&port->ip_messages, mplp->mpl_qlimit);
                ip_unlock(port);
                break;
        }
	case MACH_PORT_DNREQUESTS_SIZE: {
                if (count < MACH_PORT_DNREQUESTS_SIZE_COUNT)
                        return KERN_FAILURE;

		if (!MACH_PORT_VALID(name))
			return KERN_INVALID_RIGHT;
                
                kr = ipc_port_translate_receive(space, name, &port);
                if (kr != KERN_SUCCESS)
                        return kr;
                /* port is locked and active */
		
		kr = ipc_port_request_grow(port, *(int *)info);
		if (kr != KERN_SUCCESS)
			return kr;
		break;
	}
	case MACH_PORT_TEMPOWNER:
		if (!MACH_PORT_VALID(name))
			return KERN_INVALID_RIGHT;

		ipc_importance_task_t release_imp_task = IIT_NULL;
		natural_t assertcnt = 0;

		kr = ipc_port_translate_receive(space, name, &port);
		if (kr != KERN_SUCCESS)
			return kr;
		/* port is locked and active */

		/* 
		 * don't allow temp-owner importance donation if user
		 * associated it with a kobject already (timer, host_notify target),
		 * or is a special reply port.
		 */
		if (is_ipc_kobject(ip_kotype(port)) || port->ip_specialreply) {
			ip_unlock(port);
			return KERN_INVALID_ARGUMENT;
		}

		if (port->ip_tempowner != 0) {
			if (IIT_NULL != port->ip_imp_task) {
				release_imp_task = port->ip_imp_task;
				port->ip_imp_task = IIT_NULL;
				assertcnt = port->ip_impcount;
			}
		} else {
			assertcnt = port->ip_impcount;
		}

		port->ip_impdonation = 1;
		port->ip_tempowner = 1;
		ip_unlock(port);

#if IMPORTANCE_INHERITANCE
		/* drop assertions from previous destination task */
		if (release_imp_task != IIT_NULL) {
			assert(ipc_importance_task_is_any_receiver_type(release_imp_task));
			if (assertcnt > 0)
				ipc_importance_task_drop_internal_assertion(release_imp_task, assertcnt);
			ipc_importance_task_release(release_imp_task);
		} else if (assertcnt > 0) {
			release_imp_task = current_task()->task_imp_base;
			if (release_imp_task != IIT_NULL &&
			    ipc_importance_task_is_any_receiver_type(release_imp_task)) {
				ipc_importance_task_drop_internal_assertion(release_imp_task, assertcnt);
			}
		}
#else
		if (release_imp_task != IIT_NULL)
			ipc_importance_task_release(release_imp_task);
#endif /* IMPORTANCE_INHERITANCE */

		break;

#if IMPORTANCE_INHERITANCE
	case MACH_PORT_DENAP_RECEIVER:
	case MACH_PORT_IMPORTANCE_RECEIVER:
		if (!MACH_PORT_VALID(name))
			return KERN_INVALID_RIGHT;

		kr = ipc_port_translate_receive(space, name, &port);
		if (kr != KERN_SUCCESS)
			return kr;

		/* 
		 * don't allow importance donation if user associated
		 * it with a kobject already (timer, host_notify target),
		 * or is a special reply port.
		 */
		if (is_ipc_kobject(ip_kotype(port)) || port->ip_specialreply) {
			ip_unlock(port);
			return KERN_INVALID_ARGUMENT;
		}

		/* port is locked and active */
		port->ip_impdonation = 1;
		ip_unlock(port);

		break;
#endif /* IMPORTANCE_INHERITANCE */

        default:
		return KERN_INVALID_ARGUMENT;
                /*NOTREACHED*/
        }
	return KERN_SUCCESS;
}