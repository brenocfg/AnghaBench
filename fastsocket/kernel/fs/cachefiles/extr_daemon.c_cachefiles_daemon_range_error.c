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
struct cachefiles_cache {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kerror (char*) ; 

__attribute__((used)) static int cachefiles_daemon_range_error(struct cachefiles_cache *cache,
					 char *args)
{
	kerror("Free space limits must be in range"
	       " 0%%<=stop<cull<run<100%%");

	return -EINVAL;
}