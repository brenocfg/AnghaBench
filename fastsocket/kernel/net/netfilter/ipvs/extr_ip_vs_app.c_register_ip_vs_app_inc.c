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
struct ip_vs_app {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_vs_app_mutex ; 
 int ip_vs_app_inc_new (struct ip_vs_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
register_ip_vs_app_inc(struct ip_vs_app *app, __u16 proto, __u16 port)
{
	int result;

	mutex_lock(&__ip_vs_app_mutex);

	result = ip_vs_app_inc_new(app, proto, port);

	mutex_unlock(&__ip_vs_app_mutex);

	return result;
}