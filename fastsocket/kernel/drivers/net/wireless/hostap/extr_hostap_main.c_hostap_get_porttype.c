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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ iw_mode; scalar_t__ pseudo_adhoc; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_PORTTYPE_BSS ; 
 int /*<<< orphan*/  HFA384X_PORTTYPE_HOSTAP ; 
 int /*<<< orphan*/  HFA384X_PORTTYPE_IBSS ; 
 int /*<<< orphan*/  HFA384X_PORTTYPE_PSEUDO_IBSS ; 
 int /*<<< orphan*/  HFA384X_PORTTYPE_WDS ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MONITOR ; 
 scalar_t__ IW_MODE_REPEAT ; 

u16 hostap_get_porttype(local_info_t *local)
{
	if (local->iw_mode == IW_MODE_ADHOC && local->pseudo_adhoc)
		return HFA384X_PORTTYPE_PSEUDO_IBSS;
	if (local->iw_mode == IW_MODE_ADHOC)
		return HFA384X_PORTTYPE_IBSS;
	if (local->iw_mode == IW_MODE_INFRA)
		return HFA384X_PORTTYPE_BSS;
	if (local->iw_mode == IW_MODE_REPEAT)
		return HFA384X_PORTTYPE_WDS;
	if (local->iw_mode == IW_MODE_MONITOR)
		return HFA384X_PORTTYPE_PSEUDO_IBSS;
	return HFA384X_PORTTYPE_HOSTAP;
}