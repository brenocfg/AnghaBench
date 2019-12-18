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
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct cred {int dummy; } ;
struct cachefiles_cache {struct cred* cache_cred; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int /*<<< orphan*/  abort_creds (struct cred*) ; 
 int /*<<< orphan*/  cachefiles_begin_secure (struct cachefiles_cache*,struct cred const**) ; 
 int cachefiles_check_cache_dir (struct cachefiles_cache*,struct dentry*) ; 
 int /*<<< orphan*/  cachefiles_end_secure (struct cachefiles_cache*,struct cred const*) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int set_create_files_as (struct cred*,int /*<<< orphan*/ ) ; 

int cachefiles_determine_cache_security(struct cachefiles_cache *cache,
					struct dentry *root,
					const struct cred **_saved_cred)
{
	struct cred *new;
	int ret;

	_enter("");

	/* duplicate the cache creds for COW (the override is currently in
	 * force, so we can use prepare_creds() to do this) */
	new = prepare_creds();
	if (!new)
		return -ENOMEM;

	cachefiles_end_secure(cache, *_saved_cred);

	/* use the cache root dir's security context as the basis with
	 * which create files */
	ret = set_create_files_as(new, root->d_inode);
	if (ret < 0) {
		abort_creds(new);
		cachefiles_begin_secure(cache, _saved_cred);
		_leave(" = %d [cfa]", ret);
		return ret;
	}

	put_cred(cache->cache_cred);
	cache->cache_cred = new;

	cachefiles_begin_secure(cache, _saved_cred);
	ret = cachefiles_check_cache_dir(cache, root);

	if (ret == -EOPNOTSUPP)
		ret = 0;
	_leave(" = %d", ret);
	return ret;
}