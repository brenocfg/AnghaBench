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
 int EBADRPC ; 
 int KAUTH_ACE_ALARM ; 
 int KAUTH_ACE_AUDIT ; 
 int KAUTH_ACE_DENY ; 
 int KAUTH_ACE_PERMIT ; 
#define  NFS_ACE_ACCESS_ALLOWED_ACE_TYPE 131 
#define  NFS_ACE_ACCESS_DENIED_ACE_TYPE 130 
#define  NFS_ACE_SYSTEM_ALARM_ACE_TYPE 129 
#define  NFS_ACE_SYSTEM_AUDIT_ACE_TYPE 128 

uint32_t
nfs4_ace_nfstype_to_vfstype(uint32_t nfsacetype, int *errorp)
{
	switch (nfsacetype) {
	case NFS_ACE_ACCESS_ALLOWED_ACE_TYPE:
		return KAUTH_ACE_PERMIT;
	case NFS_ACE_ACCESS_DENIED_ACE_TYPE:
		return KAUTH_ACE_DENY;
	case NFS_ACE_SYSTEM_AUDIT_ACE_TYPE:
		return KAUTH_ACE_AUDIT;
	case NFS_ACE_SYSTEM_ALARM_ACE_TYPE:
		return KAUTH_ACE_ALARM;
	}
	*errorp = EBADRPC;
	return 0;
}