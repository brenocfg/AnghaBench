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
 int /*<<< orphan*/  _enter (char*,char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 unsigned long cachefiles_debug ; 
 int /*<<< orphan*/  kerror (char*) ; 
 unsigned long simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cachefiles_daemon_debug(struct cachefiles_cache *cache, char *args)
{
	unsigned long mask;

	_enter(",%s", args);

	mask = simple_strtoul(args, &args, 0);
	if (args[0] != '\0')
		goto inval;

	cachefiles_debug = mask;
	_leave(" = 0");
	return 0;

inval:
	kerror("debug command requires mask");
	return -EINVAL;
}