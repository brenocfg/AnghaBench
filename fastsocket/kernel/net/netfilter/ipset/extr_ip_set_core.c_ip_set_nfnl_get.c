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
struct ip_set {int dummy; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ip_set_get_byname (char const*,struct ip_set**) ; 
 int /*<<< orphan*/  nfnl_lock () ; 
 int /*<<< orphan*/  nfnl_unlock () ; 

ip_set_id_t
ip_set_nfnl_get(const char *name)
{
	struct ip_set *s;
	ip_set_id_t index;

	nfnl_lock();
	index = ip_set_get_byname(name, &s);
	nfnl_unlock();

	return index;
}