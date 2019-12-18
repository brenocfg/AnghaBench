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
struct iattr {int ia_valid; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mode; } ;
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
 int /*<<< orphan*/  __constant_htonl (int) ; 
 int /*<<< orphan*/  const htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_current_server_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xdr_encode_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline __be32 *
xdr_encode_sattr(__be32 *p, struct iattr *attr)
{
	const __be32 not_set = __constant_htonl(0xFFFFFFFF);

	*p++ = (attr->ia_valid & ATTR_MODE) ? htonl(attr->ia_mode) : not_set;
	*p++ = (attr->ia_valid & ATTR_UID) ? htonl(attr->ia_uid) : not_set;
	*p++ = (attr->ia_valid & ATTR_GID) ? htonl(attr->ia_gid) : not_set;
	*p++ = (attr->ia_valid & ATTR_SIZE) ? htonl(attr->ia_size) : not_set;

	if (attr->ia_valid & ATTR_ATIME_SET) {
		p = xdr_encode_time(p, &attr->ia_atime);
	} else if (attr->ia_valid & ATTR_ATIME) {
		p = xdr_encode_current_server_time(p, &attr->ia_atime);
	} else {
		*p++ = not_set;
		*p++ = not_set;
	}

	if (attr->ia_valid & ATTR_MTIME_SET) {
		p = xdr_encode_time(p, &attr->ia_mtime);
	} else if (attr->ia_valid & ATTR_MTIME) {
		p = xdr_encode_current_server_time(p, &attr->ia_mtime);
	} else {
		*p++ = not_set;	
		*p++ = not_set;
	}
  	return p;
}