#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mach_port_status_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
struct TYPE_13__ {int /*<<< orphan*/  mpl_qlimit; } ;
typedef  TYPE_3__ mach_port_limits_t ;
typedef  scalar_t__ mach_port_info_t ;
struct TYPE_14__ {int /*<<< orphan*/  mpie_boost_cnt; int /*<<< orphan*/  mpie_status; } ;
typedef  TYPE_4__ mach_port_info_ext_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ ipc_space_t ;
typedef  TYPE_5__* ipc_port_t ;
typedef  TYPE_6__* ipc_port_request_t ;
struct TYPE_16__ {TYPE_2__* ipr_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  imq_qlimit; } ;
struct TYPE_15__ {int /*<<< orphan*/  ip_impcount; TYPE_6__* ip_requests; TYPE_1__ ip_messages; } ;
struct TYPE_12__ {int its_size; } ;

/* Variables and functions */
 TYPE_6__* IPR_NULL ; 
 scalar_t__ IS_NULL ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_INVALID_RIGHT ; 
 int /*<<< orphan*/  KERN_INVALID_TASK ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  MACH_PORT_DNREQUESTS_SIZE 131 
 int /*<<< orphan*/  MACH_PORT_DNREQUESTS_SIZE_COUNT ; 
#define  MACH_PORT_INFO_EXT 130 
 int /*<<< orphan*/  MACH_PORT_INFO_EXT_COUNT ; 
#define  MACH_PORT_LIMITS_INFO 129 
 int /*<<< orphan*/  MACH_PORT_LIMITS_INFO_COUNT ; 
#define  MACH_PORT_RECEIVE_STATUS 128 
 int /*<<< orphan*/  MACH_PORT_RECEIVE_STATUS_COUNT ; 
 int /*<<< orphan*/  MACH_PORT_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (TYPE_5__*) ; 
 int /*<<< orphan*/  ipc_port_translate_receive (scalar_t__,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  mach_port_get_status_helper (TYPE_5__*,int /*<<< orphan*/ *) ; 

kern_return_t
mach_port_get_attributes(
	ipc_space_t		space,
	mach_port_name_t	name,
	int			flavor,
        mach_port_info_t	info,
        mach_msg_type_number_t	*count)
{
	ipc_port_t port;
	kern_return_t kr;

	if (space == IS_NULL)
		return KERN_INVALID_TASK;

        switch (flavor) {
        case MACH_PORT_LIMITS_INFO: {
                mach_port_limits_t *lp = (mach_port_limits_t *)info;

                if (*count < MACH_PORT_LIMITS_INFO_COUNT)
                        return KERN_FAILURE;

                if (!MACH_PORT_VALID(name)) {
			*count = 0;
			break;
		}
			
                kr = ipc_port_translate_receive(space, name, &port);
                if (kr != KERN_SUCCESS)
                        return kr;
                /* port is locked and active */

                lp->mpl_qlimit = port->ip_messages.imq_qlimit;
                *count = MACH_PORT_LIMITS_INFO_COUNT;
                ip_unlock(port);
                break;
        }

        case MACH_PORT_RECEIVE_STATUS: {
		mach_port_status_t *statusp = (mach_port_status_t *)info;
		
		if (*count < MACH_PORT_RECEIVE_STATUS_COUNT)
			return KERN_FAILURE;

		if (!MACH_PORT_VALID(name))
			return KERN_INVALID_RIGHT;

		kr = ipc_port_translate_receive(space, name, &port);
		if (kr != KERN_SUCCESS)
			return kr;
		/* port is locked and active */
		mach_port_get_status_helper(port, statusp);
		*count = MACH_PORT_RECEIVE_STATUS_COUNT;
		ip_unlock(port);
		break;
	}
	
	case MACH_PORT_DNREQUESTS_SIZE: {
		ipc_port_request_t	table;
		
                if (*count < MACH_PORT_DNREQUESTS_SIZE_COUNT)
                        return KERN_FAILURE;

		if (!MACH_PORT_VALID(name)) {
			*(int *)info = 0;
			break;
		}

                kr = ipc_port_translate_receive(space, name, &port);
                if (kr != KERN_SUCCESS)
                        return kr;
                /* port is locked and active */
		
		table = port->ip_requests;
		if (table == IPR_NULL)
			*(int *)info = 0;
		else
			*(int *)info = table->ipr_size->its_size;
                *count = MACH_PORT_DNREQUESTS_SIZE_COUNT;
                ip_unlock(port);
		break;
	}

	case MACH_PORT_INFO_EXT: {
		mach_port_info_ext_t *mp_info = (mach_port_info_ext_t *)info;
		if (*count < MACH_PORT_INFO_EXT_COUNT)
			return KERN_FAILURE;
			
		if (!MACH_PORT_VALID(name))
			return KERN_INVALID_RIGHT;
		
		kr = ipc_port_translate_receive(space, name, &port);
		if (kr != KERN_SUCCESS)
			return kr;
		/* port is locked and active */
		mach_port_get_status_helper(port, &mp_info->mpie_status);
		mp_info->mpie_boost_cnt = port->ip_impcount;
		*count = MACH_PORT_INFO_EXT_COUNT;
		ip_unlock(port);
		break;
	}

        default:
		return KERN_INVALID_ARGUMENT;
                /*NOTREACHED*/
        }                

	return KERN_SUCCESS;
}