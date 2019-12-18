#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipw2100_priv {int /*<<< orphan*/  msg_free_stat; int /*<<< orphan*/  msg_free_list; TYPE_1__* msg_buffers; int /*<<< orphan*/  msg_pend_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IPW_COMMAND_POOL_SIZE ; 
 int /*<<< orphan*/  SET_STAT (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_msg_initialize(struct ipw2100_priv *priv)
{
	int i;

	INIT_LIST_HEAD(&priv->msg_free_list);
	INIT_LIST_HEAD(&priv->msg_pend_list);

	for (i = 0; i < IPW_COMMAND_POOL_SIZE; i++)
		list_add_tail(&priv->msg_buffers[i].list, &priv->msg_free_list);
	SET_STAT(&priv->msg_free_stat, i);

	return 0;
}