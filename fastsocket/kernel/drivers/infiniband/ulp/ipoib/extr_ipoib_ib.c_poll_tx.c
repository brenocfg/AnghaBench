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
struct ipoib_dev_priv {scalar_t__ send_wc; int /*<<< orphan*/  dev; int /*<<< orphan*/  send_cq; } ;

/* Variables and functions */
 int MAX_SEND_CQE ; 
 int ib_poll_cq (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ipoib_ib_handle_tx_wc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int poll_tx(struct ipoib_dev_priv *priv)
{
	int n, i;

	n = ib_poll_cq(priv->send_cq, MAX_SEND_CQE, priv->send_wc);
	for (i = 0; i < n; ++i)
		ipoib_ib_handle_tx_wc(priv->dev, priv->send_wc + i);

	return n == MAX_SEND_CQE;
}