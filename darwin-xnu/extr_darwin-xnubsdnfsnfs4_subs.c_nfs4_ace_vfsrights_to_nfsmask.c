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
 int KAUTH_ACE_GENERIC_ALL ; 
 int KAUTH_ACE_GENERIC_EXECUTE ; 
 int KAUTH_ACE_GENERIC_READ ; 
 int KAUTH_ACE_GENERIC_WRITE ; 
 int KAUTH_VNODE_ADD_FILE ; 
 int KAUTH_VNODE_ADD_SUBDIRECTORY ; 
 int KAUTH_VNODE_APPEND_DATA ; 
 int KAUTH_VNODE_CHANGE_OWNER ; 
 int KAUTH_VNODE_DELETE ; 
 int KAUTH_VNODE_DELETE_CHILD ; 
 int KAUTH_VNODE_EXECUTE ; 
 int KAUTH_VNODE_LIST_DIRECTORY ; 
 int KAUTH_VNODE_READ_ATTRIBUTES ; 
 int KAUTH_VNODE_READ_DATA ; 
 int KAUTH_VNODE_READ_EXTATTRIBUTES ; 
 int KAUTH_VNODE_READ_SECURITY ; 
 int KAUTH_VNODE_SYNCHRONIZE ; 
 int KAUTH_VNODE_WRITE_ATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int KAUTH_VNODE_WRITE_EXTATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_SECURITY ; 
 int NFS_ACE_ADD_FILE ; 
 int NFS_ACE_ADD_SUBDIRECTORY ; 
 int NFS_ACE_APPEND_DATA ; 
 int NFS_ACE_DELETE ; 
 int NFS_ACE_DELETE_CHILD ; 
 int NFS_ACE_EXECUTE ; 
 int NFS_ACE_GENERIC_EXECUTE ; 
 int NFS_ACE_GENERIC_READ ; 
 int NFS_ACE_GENERIC_WRITE ; 
 int NFS_ACE_LIST_DIRECTORY ; 
 int NFS_ACE_READ_ACL ; 
 int NFS_ACE_READ_ATTRIBUTES ; 
 int NFS_ACE_READ_DATA ; 
 int NFS_ACE_READ_NAMED_ATTRS ; 
 int NFS_ACE_SYNCHRONIZE ; 
 int NFS_ACE_WRITE_ACL ; 
 int NFS_ACE_WRITE_ATTRIBUTES ; 
 int NFS_ACE_WRITE_DATA ; 
 int NFS_ACE_WRITE_NAMED_ATTRS ; 
 int NFS_ACE_WRITE_OWNER ; 

uint32_t
nfs4_ace_vfsrights_to_nfsmask(uint32_t vfsrights)
{
	uint32_t nfsmask = 0;

	if (vfsrights & KAUTH_VNODE_READ_DATA)
		nfsmask |= NFS_ACE_READ_DATA;
	if (vfsrights & KAUTH_VNODE_LIST_DIRECTORY)
		nfsmask |= NFS_ACE_LIST_DIRECTORY;
	if (vfsrights & KAUTH_VNODE_WRITE_DATA)
		nfsmask |= NFS_ACE_WRITE_DATA;
	if (vfsrights & KAUTH_VNODE_ADD_FILE)
		nfsmask |= NFS_ACE_ADD_FILE;
	if (vfsrights & KAUTH_VNODE_APPEND_DATA)
		nfsmask |= NFS_ACE_APPEND_DATA;
	if (vfsrights & KAUTH_VNODE_ADD_SUBDIRECTORY)
		nfsmask |= NFS_ACE_ADD_SUBDIRECTORY;
	if (vfsrights & KAUTH_VNODE_READ_EXTATTRIBUTES)
		nfsmask |= NFS_ACE_READ_NAMED_ATTRS;
	if (vfsrights & KAUTH_VNODE_WRITE_EXTATTRIBUTES)
		nfsmask |= NFS_ACE_WRITE_NAMED_ATTRS;
	if (vfsrights & KAUTH_VNODE_EXECUTE)
		nfsmask |= NFS_ACE_EXECUTE;
	if (vfsrights & KAUTH_VNODE_DELETE_CHILD)
		nfsmask |= NFS_ACE_DELETE_CHILD;
	if (vfsrights & KAUTH_VNODE_READ_ATTRIBUTES)
		nfsmask |= NFS_ACE_READ_ATTRIBUTES;
	if (vfsrights & KAUTH_VNODE_WRITE_ATTRIBUTES)
		nfsmask |= NFS_ACE_WRITE_ATTRIBUTES;
	if (vfsrights & KAUTH_VNODE_DELETE)
		nfsmask |= NFS_ACE_DELETE;
	if (vfsrights & KAUTH_VNODE_READ_SECURITY)
		nfsmask |= NFS_ACE_READ_ACL;
	if (vfsrights & KAUTH_VNODE_WRITE_SECURITY)
		nfsmask |= NFS_ACE_WRITE_ACL;
	if (vfsrights & KAUTH_VNODE_CHANGE_OWNER)
		nfsmask |= NFS_ACE_WRITE_OWNER;
	if (vfsrights & KAUTH_VNODE_SYNCHRONIZE)
		nfsmask |= NFS_ACE_SYNCHRONIZE;
	if (vfsrights & KAUTH_ACE_GENERIC_READ)
		nfsmask |= NFS_ACE_GENERIC_READ;
	if (vfsrights & KAUTH_ACE_GENERIC_WRITE)
		nfsmask |= NFS_ACE_GENERIC_WRITE;
	if (vfsrights & KAUTH_ACE_GENERIC_EXECUTE)
		nfsmask |= NFS_ACE_GENERIC_EXECUTE;
	if (vfsrights & KAUTH_ACE_GENERIC_ALL)
		nfsmask |= (KAUTH_ACE_GENERIC_READ|KAUTH_ACE_GENERIC_WRITE|NFS_ACE_GENERIC_EXECUTE);

	return (nfsmask);
}