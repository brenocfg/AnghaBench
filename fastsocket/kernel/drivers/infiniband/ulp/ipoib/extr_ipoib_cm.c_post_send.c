#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int num_sge; unsigned int wr_id; } ;
struct ipoib_dev_priv {TYPE_2__ tx_wr; TYPE_1__* tx_sge; } ;
struct ipoib_cm_tx {int /*<<< orphan*/  qp; } ;
struct ib_send_wr {int dummy; } ;
struct TYPE_3__ {int length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 unsigned int IPOIB_OP_CM ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_2__*,struct ib_send_wr**) ; 

__attribute__((used)) static inline int post_send(struct ipoib_dev_priv *priv,
			    struct ipoib_cm_tx *tx,
			    unsigned int wr_id,
			    u64 addr, int len)
{
	struct ib_send_wr *bad_wr;

	priv->tx_sge[0].addr          = addr;
	priv->tx_sge[0].length        = len;

	priv->tx_wr.num_sge	= 1;
	priv->tx_wr.wr_id	= wr_id | IPOIB_OP_CM;

	return ib_post_send(tx->qp, &priv->tx_wr, &bad_wr);
}