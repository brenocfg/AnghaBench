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
struct cachefiles_cache {scalar_t__ frun_percent; scalar_t__ fcull_percent; scalar_t__ fstop_percent; scalar_t__ brun_percent; scalar_t__ bcull_percent; scalar_t__ bstop_percent; scalar_t__ tag; int /*<<< orphan*/  flags; int /*<<< orphan*/  rootdirname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CACHEFILES_READY ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,char*) ; 
 int cachefiles_daemon_add_cache (struct cachefiles_cache*) ; 
 int /*<<< orphan*/  kerror (char*) ; 
 scalar_t__ kstrdup (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cachefiles_daemon_bind(struct cachefiles_cache *cache, char *args)
{
	_enter("{%u,%u,%u,%u,%u,%u},%s",
	       cache->frun_percent,
	       cache->fcull_percent,
	       cache->fstop_percent,
	       cache->brun_percent,
	       cache->bcull_percent,
	       cache->bstop_percent,
	       args);

	/* start by checking things over */
	ASSERT(cache->fstop_percent >= 0 &&
	       cache->fstop_percent < cache->fcull_percent &&
	       cache->fcull_percent < cache->frun_percent &&
	       cache->frun_percent  < 100);

	ASSERT(cache->bstop_percent >= 0 &&
	       cache->bstop_percent < cache->bcull_percent &&
	       cache->bcull_percent < cache->brun_percent &&
	       cache->brun_percent  < 100);

	if (*args) {
		kerror("'bind' command doesn't take an argument");
		return -EINVAL;
	}

	if (!cache->rootdirname) {
		kerror("No cache directory specified");
		return -EINVAL;
	}

	/* don't permit already bound caches to be re-bound */
	if (test_bit(CACHEFILES_READY, &cache->flags)) {
		kerror("Cache already bound");
		return -EBUSY;
	}

	/* make sure we have copies of the tag and dirname strings */
	if (!cache->tag) {
		/* the tag string is released by the fops->release()
		 * function, so we don't release it on error here */
		cache->tag = kstrdup("CacheFiles", GFP_KERNEL);
		if (!cache->tag)
			return -ENOMEM;
	}

	/* add the cache */
	return cachefiles_daemon_add_cache(cache);
}