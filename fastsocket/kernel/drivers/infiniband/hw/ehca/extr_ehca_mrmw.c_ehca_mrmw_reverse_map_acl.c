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
typedef  int u32 ;

/* Variables and functions */
 int const HIPZ_ACCESSCTRL_L_WRITE ; 
 int const HIPZ_ACCESSCTRL_MW_BIND ; 
 int const HIPZ_ACCESSCTRL_R_ATOMIC ; 
 int const HIPZ_ACCESSCTRL_R_READ ; 
 int const HIPZ_ACCESSCTRL_R_WRITE ; 
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_MW_BIND ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 

void ehca_mrmw_reverse_map_acl(const u32 *hipz_acl,
			       int *ib_acl) /*OUT*/
{
	*ib_acl = 0;
	if (*hipz_acl & HIPZ_ACCESSCTRL_R_READ)
		*ib_acl |= IB_ACCESS_REMOTE_READ;
	if (*hipz_acl & HIPZ_ACCESSCTRL_R_WRITE)
		*ib_acl |= IB_ACCESS_REMOTE_WRITE;
	if (*hipz_acl & HIPZ_ACCESSCTRL_R_ATOMIC)
		*ib_acl |= IB_ACCESS_REMOTE_ATOMIC;
	if (*hipz_acl & HIPZ_ACCESSCTRL_L_WRITE)
		*ib_acl |= IB_ACCESS_LOCAL_WRITE;
	if (*hipz_acl & HIPZ_ACCESSCTRL_MW_BIND)
		*ib_acl |= IB_ACCESS_MW_BIND;
}