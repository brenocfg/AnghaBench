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
struct net_device {int dummy; } ;
struct ipoib_ah {struct ib_ah* ah; int /*<<< orphan*/  ref; scalar_t__ last_send; struct net_device* dev; } ;
struct ib_pd {int dummy; } ;
struct ib_ah_attr {int dummy; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ipoib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ib_ah*) ; 
 struct ib_ah* ib_create_ah (struct ib_pd*,struct ib_ah_attr*) ; 
 int /*<<< orphan*/  ipoib_dbg (int /*<<< orphan*/ ,char*,struct ib_ah*) ; 
 int /*<<< orphan*/  kfree (struct ipoib_ah*) ; 
 struct ipoib_ah* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 

struct ipoib_ah *ipoib_create_ah(struct net_device *dev,
				 struct ib_pd *pd, struct ib_ah_attr *attr)
{
	struct ipoib_ah *ah;
	struct ib_ah *vah;

	ah = kmalloc(sizeof *ah, GFP_KERNEL);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	ah->dev       = dev;
	ah->last_send = 0;
	kref_init(&ah->ref);

	vah = ib_create_ah(pd, attr);
	if (IS_ERR(vah)) {
		kfree(ah);
		ah = (struct ipoib_ah *)vah;
	} else {
		ah->ah = vah;
		ipoib_dbg(netdev_priv(dev), "Created ah %p\n", ah->ah);
	}

	return ah;
}