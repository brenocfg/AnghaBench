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
struct ip_vs_app {int /*<<< orphan*/  usecnt; int /*<<< orphan*/  app; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ip_vs_app_get (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int ip_vs_app_inc_get(struct ip_vs_app *inc)
{
	int result;

	atomic_inc(&inc->usecnt);
	if (unlikely((result = ip_vs_app_get(inc->app)) != 1))
		atomic_dec(&inc->usecnt);
	return result;
}