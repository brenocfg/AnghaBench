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

/* Variables and functions */
#define  NFSERR_ADMIN_REVOKED 133 
#define  NFSERR_BAD_STATEID 132 
#define  NFSERR_EXPIRED 131 
#define  NFSERR_GRACE 130 
#define  NFSERR_OLD_STATEID 129 
#define  NFSERR_STALE_STATEID 128 

int
nfs_mount_state_error_delegation_lost(int error)
{
	switch (error) {
	case NFSERR_STALE_STATEID:
	case NFSERR_ADMIN_REVOKED:
	case NFSERR_EXPIRED:
	case NFSERR_OLD_STATEID:
	case NFSERR_BAD_STATEID:
	case NFSERR_GRACE: /* ugh! (stupid) RFC 3530 specifically disallows CLAIM_DELEGATE_CUR during grace period? */
		return (1);
	}
	return (0);
}