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
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int NFS_UINT_MAXLEN ; 
 scalar_t__ nfs_idmap_request_key (char const*,size_t,char const*,char*,int) ; 
 int strict_strtol (char*,int,long*) ; 

__attribute__((used)) static int nfs_idmap_lookup_id(const char *name, size_t namelen,
				const char *type, __u32 *id)
{
	char id_str[NFS_UINT_MAXLEN];
	long id_long;
	ssize_t data_size;
	int ret = 0;

	data_size = nfs_idmap_request_key(name, namelen, type, id_str, NFS_UINT_MAXLEN);
	if (data_size <= 0) {
		ret = -EINVAL;
	} else {
		ret = strict_strtol(id_str, 10, &id_long);
		*id = (__u32)id_long;
	}
	return ret;
}