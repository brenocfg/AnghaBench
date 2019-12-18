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

/* Variables and functions */
 int EAGAIN ; 
 int IPSET_ERR_FIND_TYPE ; 
 int /*<<< orphan*/  nfnl_lock () ; 
 int /*<<< orphan*/  nfnl_unlock () ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 scalar_t__ request_module (char*,char const*) ; 

__attribute__((used)) static int
try_to_load_type(const char *name)
{
	nfnl_unlock();
	pr_debug("try to load ip_set_%s\n", name);
	if (request_module("ip_set_%s", name) < 0) {
		pr_warning("Can't find ip_set type %s\n", name);
		nfnl_lock();
		return -IPSET_ERR_FIND_TYPE;
	}
	nfnl_lock();
	return -EAGAIN;
}