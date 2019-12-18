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
struct rtnl_link {int /*<<< orphan*/ * doit; } ;
typedef  int /*<<< orphan*/ * rtnl_doit_func ;

/* Variables and functions */
 size_t PF_UNSPEC ; 
 int RTNL_FAMILY_MAX ; 
 struct rtnl_link** rtnl_msg_handlers ; 

__attribute__((used)) static rtnl_doit_func rtnl_get_doit(int protocol, int msgindex)
{
	struct rtnl_link *tab;

	if (protocol <= RTNL_FAMILY_MAX)
		tab = rtnl_msg_handlers[protocol];
	else
		tab = NULL;

	if (tab == NULL || tab[msgindex].doit == NULL)
		tab = rtnl_msg_handlers[PF_UNSPEC];

	return tab ? tab[msgindex].doit : NULL;
}