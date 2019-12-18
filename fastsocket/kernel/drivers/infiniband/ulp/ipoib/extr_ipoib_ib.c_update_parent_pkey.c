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
typedef  int u16 ;
struct ipoib_dev_priv {int pkey; TYPE_1__* dev; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; } ;
struct TYPE_2__ {int* broadcast; } ;

/* Variables and functions */
 int ib_query_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int,int) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int update_parent_pkey(struct ipoib_dev_priv *priv)
{
	int result;
	u16 prev_pkey;

	prev_pkey = priv->pkey;
	result = ib_query_pkey(priv->ca, priv->port, 0, &priv->pkey);
	if (result) {
		ipoib_warn(priv, "ib_query_pkey port %d failed (ret = %d)\n",
			   priv->port, result);
		return result;
	}

	priv->pkey |= 0x8000;

	if (prev_pkey != priv->pkey) {
		ipoib_dbg(priv, "pkey changed from 0x%x to 0x%x\n",
			  prev_pkey, priv->pkey);
		/*
		 * Update the pkey in the broadcast address, while making sure to set
		 * the full membership bit, so that we join the right broadcast group.
		 */
		priv->dev->broadcast[8] = priv->pkey >> 8;
		priv->dev->broadcast[9] = priv->pkey & 0xff;
		return 0;
	}

	return 1;
}