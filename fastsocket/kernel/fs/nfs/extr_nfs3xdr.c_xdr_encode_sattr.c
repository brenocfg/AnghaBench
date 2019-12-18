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
struct iattr {int ia_valid; int ia_mode; int ia_uid; int ia_gid; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; scalar_t__ ia_size; } ;
typedef  int /*<<< orphan*/  __u64 ;
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
 int S_IALLUGO ; 
 void* htonl (int) ; 
 int /*<<< orphan*/ * xdr_encode_hyper (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xdr_encode_time3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* xdr_one ; 
 void* xdr_two ; 
 void* xdr_zero ; 

__attribute__((used)) static inline __be32 *
xdr_encode_sattr(__be32 *p, struct iattr *attr)
{
	if (attr->ia_valid & ATTR_MODE) {
		*p++ = xdr_one;
		*p++ = htonl(attr->ia_mode & S_IALLUGO);
	} else {
		*p++ = xdr_zero;
	}
	if (attr->ia_valid & ATTR_UID) {
		*p++ = xdr_one;
		*p++ = htonl(attr->ia_uid);
	} else {
		*p++ = xdr_zero;
	}
	if (attr->ia_valid & ATTR_GID) {
		*p++ = xdr_one;
		*p++ = htonl(attr->ia_gid);
	} else {
		*p++ = xdr_zero;
	}
	if (attr->ia_valid & ATTR_SIZE) {
		*p++ = xdr_one;
		p = xdr_encode_hyper(p, (__u64) attr->ia_size);
	} else {
		*p++ = xdr_zero;
	}
	if (attr->ia_valid & ATTR_ATIME_SET) {
		*p++ = xdr_two;
		p = xdr_encode_time3(p, &attr->ia_atime);
	} else if (attr->ia_valid & ATTR_ATIME) {
		*p++ = xdr_one;
	} else {
		*p++ = xdr_zero;
	}
	if (attr->ia_valid & ATTR_MTIME_SET) {
		*p++ = xdr_two;
		p = xdr_encode_time3(p, &attr->ia_mtime);
	} else if (attr->ia_valid & ATTR_MTIME) {
		*p++ = xdr_one;
	} else {
		*p++ = xdr_zero;
	}
	return p;
}