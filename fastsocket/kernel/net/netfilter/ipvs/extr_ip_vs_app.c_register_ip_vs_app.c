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
struct ip_vs_app {int /*<<< orphan*/  a_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_vs_app_mutex ; 
 int /*<<< orphan*/  ip_vs_app_list ; 
 int /*<<< orphan*/  ip_vs_use_count_inc () ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int register_ip_vs_app(struct ip_vs_app *app)
{
	/* increase the module use count */
	ip_vs_use_count_inc();

	mutex_lock(&__ip_vs_app_mutex);

	list_add(&app->a_list, &ip_vs_app_list);

	mutex_unlock(&__ip_vs_app_mutex);

	return 0;
}