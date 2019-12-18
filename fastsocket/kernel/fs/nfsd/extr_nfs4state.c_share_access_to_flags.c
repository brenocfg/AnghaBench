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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_SHARE_ACCESS_READ ; 
 int /*<<< orphan*/  NFS4_SHARE_WANT_MASK ; 
 int RD_STATE ; 
 int WR_STATE ; 

int share_access_to_flags(u32 share_access)
{
	share_access &= ~NFS4_SHARE_WANT_MASK;

	return share_access == NFS4_SHARE_ACCESS_READ ? RD_STATE : WR_STATE;
}