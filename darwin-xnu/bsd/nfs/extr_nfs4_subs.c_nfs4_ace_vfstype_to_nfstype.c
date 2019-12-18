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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
#define  KAUTH_ACE_ALARM 131 
#define  KAUTH_ACE_AUDIT 130 
#define  KAUTH_ACE_DENY 129 
#define  KAUTH_ACE_PERMIT 128 
 int NFS_ACE_ACCESS_ALLOWED_ACE_TYPE ; 
 int NFS_ACE_ACCESS_DENIED_ACE_TYPE ; 
 int NFS_ACE_SYSTEM_ALARM_ACE_TYPE ; 
 int NFS_ACE_SYSTEM_AUDIT_ACE_TYPE ; 

uint32_t
nfs4_ace_vfstype_to_nfstype(uint32_t vfstype, int *errorp)
{
	switch (vfstype) {
	case KAUTH_ACE_PERMIT:
		return NFS_ACE_ACCESS_ALLOWED_ACE_TYPE;
	case KAUTH_ACE_DENY:
		return NFS_ACE_ACCESS_DENIED_ACE_TYPE;
	case KAUTH_ACE_AUDIT:
		return NFS_ACE_SYSTEM_AUDIT_ACE_TYPE;
	case KAUTH_ACE_ALARM:
		return NFS_ACE_SYSTEM_ALARM_ACE_TYPE;
	}
	*errorp = EINVAL;
	return 0;
}