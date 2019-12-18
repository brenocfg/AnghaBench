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
struct cachefiles_cache {char* secctx; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _enter (char*,char*) ; 
 int /*<<< orphan*/  kerror (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cachefiles_daemon_secctx(struct cachefiles_cache *cache, char *args)
{
	char *secctx;

	_enter(",%s", args);

	if (!*args) {
		kerror("Empty security context specified");
		return -EINVAL;
	}

	if (cache->secctx) {
		kerror("Second security context specified");
		return -EINVAL;
	}

	secctx = kstrdup(args, GFP_KERNEL);
	if (!secctx)
		return -ENOMEM;

	cache->secctx = secctx;
	return 0;
}