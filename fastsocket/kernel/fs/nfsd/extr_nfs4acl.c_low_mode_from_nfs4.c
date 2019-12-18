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
 unsigned short ACL_EXECUTE ; 
 unsigned short ACL_READ ; 
 unsigned short ACL_WRITE ; 
 int NFS4_ACE_DELETE_CHILD ; 
 unsigned int NFS4_ACL_DIR ; 
 int NFS4_EXECUTE_MODE ; 
 int NFS4_READ_MODE ; 
 int NFS4_WRITE_MODE ; 

__attribute__((used)) static void
low_mode_from_nfs4(u32 perm, unsigned short *mode, unsigned int flags)
{
	u32 write_mode = NFS4_WRITE_MODE;

	if (flags & NFS4_ACL_DIR)
		write_mode |= NFS4_ACE_DELETE_CHILD;
	*mode = 0;
	if ((perm & NFS4_READ_MODE) == NFS4_READ_MODE)
		*mode |= ACL_READ;
	if ((perm & write_mode) == write_mode)
		*mode |= ACL_WRITE;
	if ((perm & NFS4_EXECUTE_MODE) == NFS4_EXECUTE_MODE)
		*mode |= ACL_EXECUTE;
}