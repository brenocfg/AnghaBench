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
struct ip_vs_protocol {int /*<<< orphan*/  name; int /*<<< orphan*/  (* unregister_app ) (struct ip_vs_app*) ;} ;
struct ip_vs_app {struct ip_vs_app* timeout_table; int /*<<< orphan*/  a_list; int /*<<< orphan*/  port; int /*<<< orphan*/  name; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VS_DBG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ip_vs_protocol* ip_vs_proto_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ip_vs_app*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ip_vs_app*) ; 

__attribute__((used)) static void
ip_vs_app_inc_release(struct ip_vs_app *inc)
{
	struct ip_vs_protocol *pp;

	if (!(pp = ip_vs_proto_get(inc->protocol)))
		return;

	if (pp->unregister_app)
		pp->unregister_app(inc);

	IP_VS_DBG(9, "%s App %s:%u unregistered\n",
		  pp->name, inc->name, inc->port);

	list_del(&inc->a_list);

	kfree(inc->timeout_table);
	kfree(inc);
}