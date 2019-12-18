#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_4__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_3__ {void* tv_nsec; void* tv_sec; } ;
struct iattr {int ia_valid; TYPE_2__ ia_mtime; TYPE_1__ ia_atime; scalar_t__ ia_size; void* ia_gid; void* ia_uid; void* ia_mode; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 scalar_t__ NFS_OFFSET_MAX ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_decode_hyper (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static __be32 *
decode_sattr3(__be32 *p, struct iattr *iap)
{
	u32	tmp;

	iap->ia_valid = 0;

	if (*p++) {
		iap->ia_valid |= ATTR_MODE;
		iap->ia_mode = ntohl(*p++);
	}
	if (*p++) {
		iap->ia_valid |= ATTR_UID;
		iap->ia_uid = ntohl(*p++);
	}
	if (*p++) {
		iap->ia_valid |= ATTR_GID;
		iap->ia_gid = ntohl(*p++);
	}
	if (*p++) {
		u64	newsize;

		iap->ia_valid |= ATTR_SIZE;
		p = xdr_decode_hyper(p, &newsize);
		if (newsize <= NFS_OFFSET_MAX)
			iap->ia_size = newsize;
		else
			iap->ia_size = NFS_OFFSET_MAX;
	}
	if ((tmp = ntohl(*p++)) == 1) {	/* set to server time */
		iap->ia_valid |= ATTR_ATIME;
	} else if (tmp == 2) {		/* set to client time */
		iap->ia_valid |= ATTR_ATIME | ATTR_ATIME_SET;
		iap->ia_atime.tv_sec = ntohl(*p++);
		iap->ia_atime.tv_nsec = ntohl(*p++);
	}
	if ((tmp = ntohl(*p++)) == 1) {	/* set to server time */
		iap->ia_valid |= ATTR_MTIME;
	} else if (tmp == 2) {		/* set to client time */
		iap->ia_valid |= ATTR_MTIME | ATTR_MTIME_SET;
		iap->ia_mtime.tv_sec = ntohl(*p++);
		iap->ia_mtime.tv_nsec = ntohl(*p++);
	}
	return p;
}