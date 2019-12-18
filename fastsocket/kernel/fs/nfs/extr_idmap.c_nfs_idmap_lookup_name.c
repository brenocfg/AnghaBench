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
typedef  int /*<<< orphan*/  id_str ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int NFS_UINT_MAXLEN ; 
 scalar_t__ nfs_idmap_request_key (char*,int,char const*,char*,size_t) ; 
 int snprintf (char*,int,char*,int) ; 

__attribute__((used)) static ssize_t nfs_idmap_lookup_name(__u32 id, const char *type, char *buf, size_t buflen)
{
	char id_str[NFS_UINT_MAXLEN];
	int id_len;
	ssize_t ret;

	id_len = snprintf(id_str, sizeof(id_str), "%u", id);
	ret = nfs_idmap_request_key(id_str, id_len, type, buf, buflen);
	if (ret < 0)
		return -EINVAL;
	return ret;
}