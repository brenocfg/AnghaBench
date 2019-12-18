#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipw2100_priv {TYPE_3__* msg_buffers; int /*<<< orphan*/  pci_dev; } ;
struct ipw2100_cmd_header {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd_phys; int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {TYPE_1__ c_struct; } ;
struct TYPE_6__ {TYPE_2__ info; } ;

/* Variables and functions */
 int IPW_COMMAND_POOL_SIZE ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw2100_msg_free(struct ipw2100_priv *priv)
{
	int i;

	if (!priv->msg_buffers)
		return;

	for (i = 0; i < IPW_COMMAND_POOL_SIZE; i++) {
		pci_free_consistent(priv->pci_dev,
				    sizeof(struct ipw2100_cmd_header),
				    priv->msg_buffers[i].info.c_struct.cmd,
				    priv->msg_buffers[i].info.c_struct.
				    cmd_phys);
	}

	kfree(priv->msg_buffers);
	priv->msg_buffers = NULL;
}