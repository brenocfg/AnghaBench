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
typedef  int vdev_state_t ;
typedef  int /*<<< orphan*/  vdev_aux_t ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_AUX_BAD_LOG ; 
 int /*<<< orphan*/  VDEV_AUX_CORRUPT_DATA ; 
 int /*<<< orphan*/  VDEV_AUX_SPLIT_POOL ; 
#define  VDEV_STATE_CANT_OPEN 134 
#define  VDEV_STATE_CLOSED 133 
#define  VDEV_STATE_DEGRADED 132 
#define  VDEV_STATE_FAULTED 131 
#define  VDEV_STATE_HEALTHY 130 
#define  VDEV_STATE_OFFLINE 129 
#define  VDEV_STATE_REMOVED 128 
 char const* gettext (char*) ; 

const char *
zpool_state_to_name(vdev_state_t state, vdev_aux_t aux)
{
	switch (state) {
	case VDEV_STATE_CLOSED:
	case VDEV_STATE_OFFLINE:
		return (gettext("OFFLINE"));
	case VDEV_STATE_REMOVED:
		return (gettext("REMOVED"));
	case VDEV_STATE_CANT_OPEN:
		if (aux == VDEV_AUX_CORRUPT_DATA || aux == VDEV_AUX_BAD_LOG)
			return (gettext("FAULTED"));
		else if (aux == VDEV_AUX_SPLIT_POOL)
			return (gettext("SPLIT"));
		else
			return (gettext("UNAVAIL"));
	case VDEV_STATE_FAULTED:
		return (gettext("FAULTED"));
	case VDEV_STATE_DEGRADED:
		return (gettext("DEGRADED"));
	case VDEV_STATE_HEALTHY:
		return (gettext("ONLINE"));

	default:
		break;
	}

	return (gettext("UNKNOWN"));
}