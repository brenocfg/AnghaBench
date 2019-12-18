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
struct sw_flow_actions {scalar_t__ actions_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sw_flow_actions* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ACTIONS_BUFSIZE ; 
 struct sw_flow_actions* kmalloc (int,int /*<<< orphan*/ ) ; 

struct sw_flow_actions *ovs_flow_actions_alloc(int size)
{
	struct sw_flow_actions *sfa;

	if (size > MAX_ACTIONS_BUFSIZE)
		return ERR_PTR(-EINVAL);

	sfa = kmalloc(sizeof(*sfa) + size, GFP_KERNEL);
	if (!sfa)
		return ERR_PTR(-ENOMEM);

	sfa->actions_len = 0;
	return sfa;
}