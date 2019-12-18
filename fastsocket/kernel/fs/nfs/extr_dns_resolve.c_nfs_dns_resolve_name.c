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
struct sockaddr {int dummy; } ;
struct nfs_dns_ent {char* hostname; size_t namelen; size_t addrlen; int /*<<< orphan*/  h; int /*<<< orphan*/  addr; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENOENT ; 
 size_t EOVERFLOW ; 
 size_t ESRCH ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t do_cache_lookup_wait (int /*<<< orphan*/ *,struct nfs_dns_ent*,struct nfs_dns_ent**) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  nfs_dns_resolve ; 

ssize_t nfs_dns_resolve_name(char *name, size_t namelen,
		struct sockaddr *sa, size_t salen)
{
	struct nfs_dns_ent key = {
		.hostname = name,
		.namelen = namelen,
	};
	struct nfs_dns_ent *item = NULL;
	ssize_t ret;

	ret = do_cache_lookup_wait(&nfs_dns_resolve, &key, &item);
	if (ret == 0) {
		if (salen >= item->addrlen) {
			memcpy(sa, &item->addr, item->addrlen);
			ret = item->addrlen;
		} else
			ret = -EOVERFLOW;
		cache_put(&item->h, &nfs_dns_resolve);
	} else if (ret == -ENOENT)
		ret = -ESRCH;
	return ret;
}