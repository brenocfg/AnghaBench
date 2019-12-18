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
struct lbtf_private {int cmd_response_rxed; int /*<<< orphan*/  cmd_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  lbtf_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void lbtf_cmd_response_rx(struct lbtf_private *priv)
{
	priv->cmd_response_rxed = 1;
	queue_work(lbtf_wq, &priv->cmd_work);
}