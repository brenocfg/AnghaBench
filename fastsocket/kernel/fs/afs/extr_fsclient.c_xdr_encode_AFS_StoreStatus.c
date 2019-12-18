#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int tv_sec; } ;
struct iattr {int ia_valid; int ia_uid; int ia_gid; int ia_mode; TYPE_1__ ia_mtime; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int AFS_SET_GROUP ; 
 int AFS_SET_MODE ; 
 int AFS_SET_MTIME ; 
 int AFS_SET_OWNER ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_UID ; 
 int S_IALLUGO ; 
 void* htonl (int) ; 

__attribute__((used)) static void xdr_encode_AFS_StoreStatus(__be32 **_bp, struct iattr *attr)
{
	__be32 *bp = *_bp;
	u32 mask = 0, mtime = 0, owner = 0, group = 0, mode = 0;

	mask = 0;
	if (attr->ia_valid & ATTR_MTIME) {
		mask |= AFS_SET_MTIME;
		mtime = attr->ia_mtime.tv_sec;
	}

	if (attr->ia_valid & ATTR_UID) {
		mask |= AFS_SET_OWNER;
		owner = attr->ia_uid;
	}

	if (attr->ia_valid & ATTR_GID) {
		mask |= AFS_SET_GROUP;
		group = attr->ia_gid;
	}

	if (attr->ia_valid & ATTR_MODE) {
		mask |= AFS_SET_MODE;
		mode = attr->ia_mode & S_IALLUGO;
	}

	*bp++ = htonl(mask);
	*bp++ = htonl(mtime);
	*bp++ = htonl(owner);
	*bp++ = htonl(group);
	*bp++ = htonl(mode);
	*bp++ = 0;		/* segment size */
	*_bp = bp;
}