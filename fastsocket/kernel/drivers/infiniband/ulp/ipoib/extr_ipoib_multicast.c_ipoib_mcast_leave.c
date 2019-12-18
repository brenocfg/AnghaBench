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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  mlid; TYPE_2__ mgid; } ;
struct ipoib_mcast {TYPE_1__ mcmember; int /*<<< orphan*/  flags; int /*<<< orphan*/  mc; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_ATTACHED ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int ib_detach_mcast (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_sa_free_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_mcast_leave(struct net_device *dev, struct ipoib_mcast *mcast)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);
	int ret = 0;

	if (test_and_clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags))
		ib_sa_free_multicast(mcast->mc);

	if (test_and_clear_bit(IPOIB_MCAST_FLAG_ATTACHED, &mcast->flags)) {
		ipoib_dbg_mcast(priv, "leaving MGID %pI6\n",
				mcast->mcmember.mgid.raw);

		/* Remove ourselves from the multicast group */
		ret = ib_detach_mcast(priv->qp, &mcast->mcmember.mgid,
				      be16_to_cpu(mcast->mcmember.mlid));
		if (ret)
			ipoib_warn(priv, "ib_detach_mcast failed (result = %d)\n", ret);
	}

	return 0;
}