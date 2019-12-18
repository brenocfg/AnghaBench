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
typedef  int uid_t ;
struct svc_rqst {int dummy; } ;
struct ent {int id; int type; int /*<<< orphan*/  h; int /*<<< orphan*/  name; int /*<<< orphan*/  authname; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int IDMAP_NAMESZ ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int idmap_lookup (struct svc_rqst*,int /*<<< orphan*/ ,struct ent*,int /*<<< orphan*/ *,struct ent**) ; 
 int /*<<< orphan*/  idtoname_cache ; 
 int /*<<< orphan*/  idtoname_lookup ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rqst_authname (struct svc_rqst*) ; 
 int sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idmap_id_to_name(struct svc_rqst *rqstp, int type, uid_t id, char *name)
{
	struct ent *item, key = {
		.id = id,
		.type = type,
	};
	int ret;

	strlcpy(key.authname, rqst_authname(rqstp), sizeof(key.authname));
	ret = idmap_lookup(rqstp, idtoname_lookup, &key, &idtoname_cache, &item);
	if (ret == -ENOENT)
		return sprintf(name, "%u", id);
	if (ret)
		return ret;
	ret = strlen(item->name);
	BUG_ON(ret > IDMAP_NAMESZ);
	memcpy(name, item->name, ret);
	cache_put(&item->h, &idtoname_cache);
	return ret;
}