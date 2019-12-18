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
struct TYPE_4__ {scalar_t__ CapsuleMode; } ;
struct TYPE_5__ {TYPE_1__ TransformSetting; } ;
typedef  TYPE_2__ IPSECSA ;

/* Variables and functions */
 scalar_t__ IKE_P2_CAPSULE_NAT_TUNNEL_1 ; 
 scalar_t__ IKE_P2_CAPSULE_NAT_TUNNEL_2 ; 
 scalar_t__ IKE_P2_CAPSULE_TUNNEL ; 

bool IsIPsecSaTunnelMode(IPSECSA *sa)
{
	// Validate arguments
	if (sa == NULL)
	{
		return false;
	}

	if (sa->TransformSetting.CapsuleMode == IKE_P2_CAPSULE_TUNNEL ||
		sa->TransformSetting.CapsuleMode == IKE_P2_CAPSULE_NAT_TUNNEL_1 ||
		sa->TransformSetting.CapsuleMode == IKE_P2_CAPSULE_NAT_TUNNEL_2)
	{
		return true;
	}

	return false;
}