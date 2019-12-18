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
typedef  int u32 ;
struct TYPE_4__ {int tv_sec; int tv_nsec; } ;
struct TYPE_3__ {int tv_sec; int tv_nsec; } ;
struct iattr {int ia_valid; int ia_mode; int ia_uid; int ia_gid; int ia_size; TYPE_2__ ia_mtime; TYPE_1__ ia_atime; } ;
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
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32 *
decode_sattr(__be32 *p, struct iattr *iap)
{
	u32	tmp, tmp1;

	iap->ia_valid = 0;

	/* Sun client bug compatibility check: some sun clients seem to
	 * put 0xffff in the mode field when they mean 0xffffffff.
	 * Quoting the 4.4BSD nfs server code: Nah nah nah nah na nah.
	 */
	if ((tmp = ntohl(*p++)) != (u32)-1 && tmp != 0xffff) {
		iap->ia_valid |= ATTR_MODE;
		iap->ia_mode = tmp;
	}
	if ((tmp = ntohl(*p++)) != (u32)-1) {
		iap->ia_valid |= ATTR_UID;
		iap->ia_uid = tmp;
	}
	if ((tmp = ntohl(*p++)) != (u32)-1) {
		iap->ia_valid |= ATTR_GID;
		iap->ia_gid = tmp;
	}
	if ((tmp = ntohl(*p++)) != (u32)-1) {
		iap->ia_valid |= ATTR_SIZE;
		iap->ia_size = tmp;
	}
	tmp  = ntohl(*p++); tmp1 = ntohl(*p++);
	if (tmp != (u32)-1 && tmp1 != (u32)-1) {
		iap->ia_valid |= ATTR_ATIME | ATTR_ATIME_SET;
		iap->ia_atime.tv_sec = tmp;
		iap->ia_atime.tv_nsec = tmp1 * 1000; 
	}
	tmp  = ntohl(*p++); tmp1 = ntohl(*p++);
	if (tmp != (u32)-1 && tmp1 != (u32)-1) {
		iap->ia_valid |= ATTR_MTIME | ATTR_MTIME_SET;
		iap->ia_mtime.tv_sec = tmp;
		iap->ia_mtime.tv_nsec = tmp1 * 1000; 
		/*
		 * Passing the invalid value useconds=1000000 for mtime
		 * is a Sun convention for "set both mtime and atime to
		 * current server time".  It's needed to make permissions
		 * checks for the "touch" program across v2 mounts to
		 * Solaris and Irix boxes work correctly. See description of
		 * sattr in section 6.1 of "NFS Illustrated" by
		 * Brent Callaghan, Addison-Wesley, ISBN 0-201-32750-5
		 */
		if (tmp1 == 1000000)
			iap->ia_valid &= ~(ATTR_ATIME_SET|ATTR_MTIME_SET);
	}
	return p;
}