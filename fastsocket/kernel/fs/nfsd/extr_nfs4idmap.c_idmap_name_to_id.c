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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int u32 ;
struct svc_rqst {int dummy; } ;
struct ent {int type; char* name; int /*<<< orphan*/  h; int /*<<< orphan*/  id; int /*<<< orphan*/  authname; } ;

/* Variables and functions */
 int ENOENT ; 
 int ESRCH ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int idmap_lookup (struct svc_rqst*,int /*<<< orphan*/ ,struct ent*,int /*<<< orphan*/ *,struct ent**) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  nametoid_cache ; 
 int /*<<< orphan*/  nametoid_lookup ; 
 int /*<<< orphan*/  rqst_authname (struct svc_rqst*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
idmap_name_to_id(struct svc_rqst *rqstp, int type, const char *name, u32 namelen,
		uid_t *id)
{
	struct ent *item, key = {
		.type = type,
	};
	int ret;

	if (namelen + 1 > sizeof(key.name))
		return -ESRCH; /* nfserr_badowner */
	memcpy(key.name, name, namelen);
	key.name[namelen] = '\0';
	strlcpy(key.authname, rqst_authname(rqstp), sizeof(key.authname));
	ret = idmap_lookup(rqstp, nametoid_lookup, &key, &nametoid_cache, &item);
	if (ret == -ENOENT)
		ret = -ESRCH; /* nfserr_badowner */
	if (ret)
		return ret;
	*id = item->id;
	cache_put(&item->h, &nametoid_cache);
	return 0;
}